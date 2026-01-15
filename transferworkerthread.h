// transferworkerthread.h
#include "customtransfermodel.h"

#include <QThread>
#include <QString>
#include <QMutex>
#include <QWaitCondition>  // Qt6 推荐使用条件变量实现线程暂停/唤醒

class FileIoManager;
class FileTransferClient;

class TransferWorkerThread : public QThread
{
    Q_OBJECT
public:
    explicit TransferWorkerThread(QObject *parent = nullptr);
    ~TransferWorkerThread() override;

    void setTransferTask(const TransferFileData &fileData, const QString &savePath = "./ReceivedFiles/");
    void pauseTransfer();
    void resumeTransfer();
    void cancelTransfer();

signals:
    void transferProgressUpdated(const QString &fileName, const QString &targetDevice, qint64 transferredSize, TransferState state);
    void transferFinished(const QString &fileName, const QString &targetDevice, bool isSuccess);

protected:
    void run() override;

private:
    TransferFileData m_transferTask;
    QString m_savePath;
    bool m_isPaused;
    bool m_isCancelled;
    qint64 m_lastTransferOffset;

    FileIoManager *m_fileIoManager;
    FileTransferClient *m_fileTransferClient;

    // Qt6 新增：条件变量与互斥锁，替代 wakeUp()
    QMutex m_pauseMutex;
    QWaitCondition m_pauseCondition;

    qint64 loadBreakpointOffset(const QString &fileName, const QString &targetDevice);
    void saveBreakpointOffset(const QString &fileName, const QString &targetDevice, qint64 offset);
};
