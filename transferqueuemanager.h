#ifndef TRANSFERQUEUEMANAGER_H
#define TRANSFERQUEUEMANAGER_H

#include <QObject>
#include <QList>
#include <QString>
// 引入传输文件数据结构体（来自 CustomTransferModel）
#include "customtransfermodel.h"

class TransferQueueManager : public QObject
{
    Q_OBJECT
public:
    explicit TransferQueueManager(QObject *parent = nullptr);

    // 核心接口：添加单个传输任务到队列
    void addTaskToQueue(const TransferFileData &taskData);

    // 核心接口：从队列中移除指定任务（文件名+目标设备唯一标识）
    void removeTaskFromQueue(const QString &fileName, const QString &targetDevice);

    // 核心接口：获取队列中第一个待传输任务（状态为 TransferWaiting）
    TransferFileData getFirstPendingTask();

    // 辅助接口：获取队列总任务数
    int getQueueCount() const;

    // 辅助接口：清空整个传输队列
    void clearQueue();

    // 辅助接口：获取完整队列列表（用于调试或扩展）
    QList<TransferFileData> getFullQueue() const;

private:
    // 存储所有传输任务的队列（核心数据容器）
    QList<TransferFileData> m_transferQueue;

    // 辅助函数：查找指定任务在队列中的索引
    int findTaskIndex(const QString &fileName, const QString &targetDevice) const;
};

#endif // TRANSFERQUEUEMANAGER_H
