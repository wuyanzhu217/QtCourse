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

    QString selfSavePath = savePath + "/self_receive_";
    m_savePath = selfSavePath;
    m_lastTransferOffset = loadBreakpointOffset(fileData.fileName, fileData.targetDevice);
}

void TransferWorkerThread::pauseTransfer()
{
    QMutexLocker locker(&m_pauseMutex);
    m_isPaused = true;
}

void TransferWorkerThread::resumeTransfer()
{
    QMutexLocker locker(&m_pauseMutex);
    m_isPaused = false;
    m_pauseCondition.wakeOne();
}

void TransferWorkerThread::cancelTransfer()
{
    m_isCancelled = true;
    m_isPaused = false; // 解除暂停，确保线程能退出
}
void TransferWorkerThread::run()
{
    m_fileIoManager = new FileIoManager();
    m_fileTransferClient = new FileTransferClient();

    if (m_transferTask.filePath.isEmpty() || m_transferTask.targetDevice.isEmpty()) {
        emit transferProgressUpdated(m_transferTask.fileName, m_transferTask.targetDevice, 0, TransferFailed);
        emit transferFinished(m_transferTask.fileName, m_transferTask.targetDevice, false);
        return;
    }

    QDir saveDir(m_savePath);
    if (!saveDir.exists() && !saveDir.mkpath(".")) {
        qDebug() << "创建保存目录失败：" << m_savePath;
        emit transferProgressUpdated(m_transferTask.fileName, m_transferTask.targetDevice, 0, TransferFailed);
        emit transferFinished(m_transferTask.fileName, m_transferTask.targetDevice, false);
        return;
    }

    if (!m_fileTransferClient->connectToServer(m_transferTask.targetDevice, 9901)) {
        qDebug() << "连接目标设备失败：" << m_transferTask.targetDevice;
        emit transferProgressUpdated(m_transferTask.fileName, m_transferTask.targetDevice, 0, TransferFailed);
        emit transferFinished(m_transferTask.fileName, m_transferTask.targetDevice, false);
        return;
    }

    if (!m_fileTransferClient->sendFileHeader(m_transferTask.fileName, m_transferTask.fileSize, m_lastTransferOffset)) {
        qDebug() << "发送文件头信息失败";
        m_fileTransferClient->disconnectFromServer();
        emit transferProgressUpdated(m_transferTask.fileName, m_transferTask.targetDevice, 0, TransferFailed);
        emit transferFinished(m_transferTask.fileName, m_transferTask.targetDevice, false);
        return;
    }

    qint64 transferredSize = m_lastTransferOffset;
    emit transferProgressUpdated(m_transferTask.fileName, m_transferTask.targetDevice, transferredSize, TransferRunning);

    while (transferredSize < m_transferTask.fileSize && !m_isCancelled) {
        // Qt6 ：使用条件变量处理暂停逻辑，替代忙等
        QMutexLocker locker(&m_pauseMutex);
        while (m_isPaused && !m_isCancelled) {
            // 保存断点偏移量
            saveBreakpointOffset(m_transferTask.fileName, m_transferTask.targetDevice, transferredSize);
            emit transferProgressUpdated(m_transferTask.fileName, m_transferTask.targetDevice, transferredSize, TransferPaused);
            // 等待唤醒信号，超时 1 秒避免死锁
            m_pauseCondition.wait(&m_pauseMutex, 1000);
        }

        if (m_isCancelled) break;

        qint64 blockSize = qMin(FILE_BLOCK_SIZE, m_transferTask.fileSize - transferredSize);
        QByteArray fileBlock = m_fileIoManager->readFileBlock(m_transferTask.filePath, transferredSize, blockSize);

        if (fileBlock.isEmpty() && blockSize > 0) {
            qDebug() << "读取文件块失败，偏移量：" << transferredSize;
            saveBreakpointOffset(m_transferTask.fileName, m_transferTask.targetDevice, transferredSize);
            m_fileTransferClient->disconnectFromServer();
            emit transferProgressUpdated(m_transferTask.fileName, m_transferTask.targetDevice, transferredSize, TransferFailed);
            emit transferFinished(m_transferTask.fileName, m_transferTask.targetDevice, false);
            return;
        }

        if (!m_fileTransferClient->sendFileBlock(fileBlock)) {
            qDebug() << "发送文件块失败，偏移量：" << transferredSize;
            saveBreakpointOffset(m_transferTask.fileName, m_transferTask.targetDevice, transferredSize);
            m_fileTransferClient->disconnectFromServer();
            emit transferProgressUpdated(m_transferTask.fileName, m_transferTask.targetDevice, transferredSize, TransferFailed);
            emit transferFinished(m_transferTask.fileName, m_transferTask.targetDevice, false);
            return;
        }

        transferredSize += fileBlock.size();
        emit transferProgressUpdated(m_transferTask.fileName, m_transferTask.targetDevice, transferredSize, TransferRunning);

        this->msleep(1);
    }

    m_fileTransferClient->disconnectFromServer();
    if (m_isCancelled) {
        saveBreakpointOffset(m_transferTask.fileName, m_transferTask.targetDevice, transferredSize);
        emit transferProgressUpdated(m_transferTask.fileName, m_transferTask.targetDevice, transferredSize, TransferFailed);
        emit transferFinished(m_transferTask.fileName, m_transferTask.targetDevice, false);
    } else if (transferredSize >= m_transferTask.fileSize) {
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
