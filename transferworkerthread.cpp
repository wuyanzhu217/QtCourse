// transferworkerthread.cpp
#include "transferworkerthread.h"
#include "fileiomanager.h"
#include "filetransferclient.h"
#include <QDir>
#include <QDebug>

TransferWorkerThread::TransferWorkerThread(QObject *parent)
    : QThread(parent)
    , m_isPaused(false)
    , m_isCancelled(false)
    , m_lastTransferOffset(0)
    , m_fileIoManager(nullptr)
    , m_fileTransferClient(nullptr)
{
}

TransferWorkerThread::~TransferWorkerThread()
{
    // 安全停止线程
    if (this->isRunning()) {
        m_isCancelled = true;
        this->quit();
        this->wait();
    }

    // 释放资源
    if (m_fileIoManager) {
        delete m_fileIoManager;
        m_fileIoManager = nullptr;
    }
    if (m_fileTransferClient) {
        delete m_fileTransferClient;
        m_fileTransferClient = nullptr;
    }
}

void TransferWorkerThread::setTransferTask(const TransferFileData &fileData, const QString &savePath)
{
    m_transferTask = fileData;
    m_savePath = savePath;
    m_lastTransferOffset = loadBreakpointOffset(fileData.fileName, fileData.targetDevice);
}

void TransferWorkerThread::pauseTransfer()
{
    m_isPaused = true;
}

void TransferWorkerThread::resumeTransfer()
{
    m_isPaused = false;
    // 唤醒线程（若处于暂停阻塞状态）
    this->wakeUp();
}

void TransferWorkerThread::cancelTransfer()
{
    m_isCancelled = true;
    m_isPaused = false; // 解除暂停，确保线程能退出
}

void TransferWorkerThread::run()
{
    // 初始化工具类（线程内创建，避免跨线程资源冲突）
    m_fileIoManager = new FileIoManager();
    m_fileTransferClient = new FileTransferClient();

    // 1. 检查参数有效性
    if (m_transferTask.filePath.isEmpty() || m_transferTask.targetDevice.isEmpty()) {
        emit transferProgressUpdated(m_transferTask.fileName, m_transferTask.targetDevice, 0, TransferFailed);
        emit transferFinished(m_transferTask.fileName, m_transferTask.targetDevice, false);
        return;
    }

    // 2. 创建保存目录（接收方）
    QDir saveDir(m_savePath);
    if (!saveDir.exists()) {
        if (!saveDir.mkpath(".")) {
            qDebug() << "创建保存目录失败：" << m_savePath;
            emit transferProgressUpdated(m_transferTask.fileName, m_transferTask.targetDevice, 0, TransferFailed);
            emit transferFinished(m_transferTask.fileName, m_transferTask.targetDevice, false);
            return;
        }
    }

    // 3. 连接目标设备 TCP 服务器
    if (!m_fileTransferClient->connectToServer(m_transferTask.targetDevice, FILE_TRANSFER_PORT)) {
        qDebug() << "连接目标设备失败：" << m_transferTask.targetDevice;
        emit transferProgressUpdated(m_transferTask.fileName, m_transferTask.targetDevice, 0, TransferFailed);
        emit transferFinished(m_transferTask.fileName, m_transferTask.targetDevice, false);
        return;
    }

    // 4. 发送文件头信息（文件名、文件大小、断点偏移量）
    if (!m_fileTransferClient->sendFileHeader(m_transferTask.fileName, m_transferTask.fileSize, m_lastTransferOffset)) {
        qDebug() << "发送文件头信息失败";
        m_fileTransferClient->disconnectFromServer();
        emit transferProgressUpdated(m_transferTask.fileName, m_transferTask.targetDevice, 0, TransferFailed);
        emit transferFinished(m_transferTask.fileName, m_transferTask.targetDevice, false);
        return;
    }

    // 5. 开始分块传输文件（核心逻辑）
    qint64 transferredSize = m_lastTransferOffset;
    emit transferProgressUpdated(m_transferTask.fileName, m_transferTask.targetDevice, transferredSize, TransferRunning);

    while (transferredSize < m_transferTask.fileSize && !m_isCancelled) {
        // 处理暂停逻辑
        if (m_isPaused) {
            // 保存当前断点偏移量
            saveBreakpointOffset(m_transferTask.fileName, m_transferTask.targetDevice, transferredSize);
            emit transferProgressUpdated(m_transferTask.fileName, m_transferTask.targetDevice, transferredSize, TransferPaused);
            // 阻塞线程，直到被唤醒（继续/取消）
            this->msleep(100); // 避免忙等
            continue;
        }

        // 计算本次传输块大小（避免最后一块超出文件大小）
        qint64 blockSize = qMin(FILE_BLOCK_SIZE, m_transferTask.fileSize - transferredSize);

        // 从文件读取数据块（发送方）/ 准备接收数据块（接收方，此处以发送方为例）
        QByteArray fileBlock = m_fileIoManager->readFileBlock(m_transferTask.filePath, transferredSize, blockSize);
        if (fileBlock.isEmpty() && blockSize > 0) {
            qDebug() << "读取文件块失败，偏移量：" << transferredSize;
            saveBreakpointOffset(m_transferTask.fileName, m_transferTask.targetDevice, transferredSize);
            m_fileTransferClient->disconnectFromServer();
            emit transferProgressUpdated(m_transferTask.fileName, m_transferTask.targetDevice, transferredSize, TransferFailed);
            emit transferFinished(m_transferTask.fileName, m_transferTask.targetDevice, false);
            return;
        }

        // 发送数据块到目标设备
        if (!m_fileTransferClient->sendFileBlock(fileBlock)) {
            qDebug() << "发送文件块失败，偏移量：" << transferredSize;
            saveBreakpointOffset(m_transferTask.fileName, m_transferTask.targetDevice, transferredSize);
            m_fileTransferClient->disconnectFromServer();
            emit transferProgressUpdated(m_transferTask.fileName, m_transferTask.targetDevice, transferredSize, TransferFailed);
            emit transferFinished(m_transferTask.fileName, m_transferTask.targetDevice, false);
            return;
        }

        // 更新传输进度
        transferredSize += fileBlock.size();
        emit transferProgressUpdated(m_transferTask.fileName, m_transferTask.targetDevice, transferredSize, TransferRunning);

        // 轻微延时，避免占用过多 CPU 资源
        this->msleep(1);
    }

    // 6. 处理传输结果
    m_fileTransferClient->disconnectFromServer();
    if (m_isCancelled) {
        // 取消传输，保存断点
        saveBreakpointOffset(m_transferTask.fileName, m_transferTask.targetDevice, transferredSize);
        emit transferProgressUpdated(m_transferTask.fileName, m_transferTask.targetDevice, transferredSize, TransferFailed);
        emit transferFinished(m_transferTask.fileName, m_transferTask.targetDevice, false);
    } else if (transferredSize >= m_transferTask.fileSize) {
        // 传输完成，删除断点记录
        m_fileIoManager->deleteBreakpointRecord(m_transferTask.fileName, m_transferTask.targetDevice);
        emit transferProgressUpdated(m_transferTask.fileName, m_transferTask.targetDevice, transferredSize, TransferCompleted);
        emit transferFinished(m_transferTask.fileName, m_transferTask.targetDevice, true);
    }
}

qint64 TransferWorkerThread::loadBreakpointOffset(const QString &fileName, const QString &targetDevice)
{
    if (!m_fileIoManager) {
        return 0;
    }
    return m_fileIoManager->loadBreakpointOffset(fileName, targetDevice);
}

void TransferWorkerThread::saveBreakpointOffset(const QString &fileName, const QString &targetDevice, qint64 offset)
{
    if (!m_fileIoManager) {
        return;
    }
    m_fileIoManager->saveBreakpointOffset(fileName, targetDevice, offset);
}
