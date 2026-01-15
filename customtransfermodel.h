// customtransfermodel.h
#ifndef CUSTOMTRANSFERMODEL_H
#define CUSTOMTRANSFERMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QVariant>
#include <QDateTime>

// 传输状态枚举
enum TransferState {
    TransferWaiting = 0,    // 等待传输
    TransferRunning = 1,    // 传输中
    TransferPaused = 2,     // 已暂停
    TransferCompleted = 3,  // 传输完成
    TransferFailed = 4      // 传输失败
};

// 传输文件数据结构体
struct TransferFileData {
    QString fileName;       // 文件名（含扩展名）
    QString filePath;       // 文件本地路径（发送方）/ 保存路径（接收方）
    QString targetDevice;   // 目标设备 IP/设备名
    qint64 fileSize;        // 文件总大小（字节）
    qint64 transferredSize; // 已传输大小（字节）
    TransferState state;    // 传输状态
    QDateTime createTime;   // 加入队列时间
    float progress;         // 传输进度（0.0 ~ 100.0）
};

class CustomTransferModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    // 表格列索引
    enum TransferColumn {
        FileNameColumn = 0,
        TargetDeviceColumn,
        FileSizeColumn,
        ProgressColumn,
        StateColumn,
        CreateTimeColumn,
        ColumnCount
    };

    explicit CustomTransferModel(QObject *parent = nullptr);

    // 重写 Model 纯虚函数
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // 自定义接口：添加单条传输文件数据到队列
    void addTransferFile(const TransferFileData &fileData);
    // 自定义接口：更新文件传输进度与状态
    void updateTransferProgress(const QString &fileName, const QString &targetDevice, qint64 transferredSize, TransferState state);
    // 自定义接口：清空传输队列
    void clearTransferQueue();
    // 自定义接口：获取指定行的传输文件数据
    TransferFileData getTransferFile(int row) const;

private:
    QList<TransferFileData> m_transferFileList;  // 存储所有传输队列数据
    // 辅助函数：将传输状态转换为字符串
    QString stateToString(TransferState state) const;
    // 辅助函数：将文件大小（字节）转换为易读格式（KB/MB/GB）
    QString fileSizeToString(qint64 fileSize) const;
};

#endif // CUSTOMTRANSFERMODEL_H
