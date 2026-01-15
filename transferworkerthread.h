// transferworkerthread.h
#ifndef TRANSFERWORKERTHREAD_H
#define TRANSFERWORKERTHREAD_H

#include <QThread>
#include <QString>
#include "customtransfermodel.h"

class FileIoManager;
class FileTransferClient;

class TransferWorkerThread : public QThread
{
    Q_OBJECT
public:
    explicit TransferWorkerThread(QObject *parent = nullptr);
    ~TransferWorkerThread() override;

    // 自定义接口：设置待传输文件信息（启动线程前调用）
    void setTransferTask(const TransferFileData &fileData, const QString &savePath = "./ReceivedFiles/");
    // 自定义接口：暂停/继续传输
    void pauseTransfer();
    void resumeTransfer();
    // 自定义接口：取消传输
    void cancelTransfer();

signals:
    // 传输进度更新信号（传递给主线程更新 Model/View）
    void transferProgressUpdated(const QString &fileName, const QString &targetDevice, qint64 transferredSize, TransferState state);
    // 传输完成/失败通知信号
    void transferFinished(const QString &fileName, const QString &targetDevice, bool isSuccess);

protected:
    void run() override;  // 线程入口函数，执行后台传输任务

private:
    // 传输任务参数
    TransferFileData m_transferTask;
    QString m_savePath;          // 接收方文件保存路径
    bool m_isPaused;             // 暂停标记
    bool m_isCancelled;          // 取消标记
    qint64 m_lastTransferOffset; // 断点续传偏移量（上次中断位置）

    // 核心工具类指针
    FileIoManager *m_fileIoManager;
    FileTransferClient *m_fileTransferClient;

    // 辅助函数：加载断点续传偏移量
    qint64 loadBreakpointOffset(const QString &fileName, const QString &targetDevice);
    // 辅助函数：保存断点续传偏移量
    void saveBreakpointOffset(const QString &fileName, const QString &targetDevice, qint64 offset);
};

#endif // TRANSFERWORKERTHREAD_H
