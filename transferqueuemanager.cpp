#include "transferqueuemanager.h"
#include <QDebug>

TransferQueueManager::TransferQueueManager(QObject *parent)
    : QObject(parent)
{
    // 初始化空队列
}

void TransferQueueManager::addTaskToQueue(const TransferFileData &taskData)
{
    // 避免重复添加相同任务（文件名+目标设备唯一判定）
    int existingIndex = findTaskIndex(taskData.fileName, taskData.targetDevice);
    if (existingIndex != -1) {
        qDebug() << "任务已存在于队列中，跳过添加：" << taskData.fileName;
        return;
    }

    // 添加任务到队列尾部（先进先出，FIFO 原则，符合常规传输队列逻辑）
    m_transferQueue.append(taskData);
    qDebug() << "任务已添加到队列：" << taskData.fileName << "，当前队列总数：" << m_transferQueue.count();
}

void TransferQueueManager::removeTaskFromQueue(const QString &fileName, const QString &targetDevice)
{
    int taskIndex = findTaskIndex(fileName, targetDevice);
    if (taskIndex == -1) {
        qDebug() << "队列中未找到该任务，跳过移除：" << fileName;
        return;
    }

    // 从队列中移除指定任务
    m_transferQueue.removeAt(taskIndex);
    qDebug() << "任务已从队列移除：" << fileName << "，当前队列总数：" << m_transferQueue.count();
}

TransferFileData TransferQueueManager::getFirstPendingTask()
{
    // 遍历队列，查找第一个状态为「等待传输」（TransferWaiting）的任务
    for (const TransferFileData &task : m_transferQueue) {
        if (task.state == TransferWaiting) {
            return task;
        }
    }

    // 无待传输任务，返回空结构体
    return TransferFileData();
}

int TransferQueueManager::getQueueCount() const
{
    // 返回队列总任务数
    return m_transferQueue.count();
}

void TransferQueueManager::clearQueue()
{
    // 清空整个传输队列
    m_transferQueue.clear();
    qDebug() << "传输队列已清空，当前队列总数：" << m_transferQueue.count();
}

QList<TransferFileData> TransferQueueManager::getFullQueue() const
{
    // 返回完整队列列表（用于扩展功能，如队列排序、优先级调整）
    return m_transferQueue;
}

int TransferQueueManager::findTaskIndex(const QString &fileName, const QString &targetDevice) const
{
    // 遍历队列，查找匹配「文件名+目标设备」的任务索引
    for (int i = 0; i < m_transferQueue.count(); ++i) {
        const TransferFileData &task = m_transferQueue.at(i);
        if (task.fileName == fileName && task.targetDevice == targetDevice) {
            return i;
        }
    }

    // 未找到匹配任务，返回 -1
    return -1;
}
