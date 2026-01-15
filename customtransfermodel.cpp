// customtransfermodel.cpp
#include "customtransfermodel.h"
#include <QColor>
#include <QDebug>

CustomTransferModel::CustomTransferModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

int CustomTransferModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_transferFileList.count();
}

int CustomTransferModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return ColumnCount;
}

QVariant CustomTransferModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_transferFileList.count() || index.column() >= ColumnCount)
        return QVariant();

    const TransferFileData &fileData = m_transferFileList.at(index.row());

    // 显示角色：表格单元格内容
    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case FileNameColumn:
            return fileData.fileName;
        case TargetDeviceColumn:
            return fileData.targetDevice;
        case FileSizeColumn:
            return fileSizeToString(fileData.fileSize);
        case ProgressColumn:
            return QString("%1%").arg(QString::number(fileData.progress, 'f', 1));
        case StateColumn:
            return stateToString(fileData.state);
        case CreateTimeColumn:
            return fileData.createTime.toString("yyyy-MM-dd HH:mm:ss");
        default:
            return QVariant();
        }
    }

    // 前景色角色：根据传输状态设置文字颜色
    if (role == Qt::ForegroundRole) {
        switch (fileData.state) {
        case TransferCompleted:
            return QColor(Qt::darkGreen);
        case TransferFailed:
            return QColor(Qt::red);
        case TransferRunning:
            return QColor(Qt::darkBlue);
        default:
            return QColor(Qt::black);
        }
    }

    // 进度条展示（可选：结合 QStyledItemDelegate 实现单元格内进度条）
    if (role == Qt::UserRole && index.column() == ProgressColumn) {
        return fileData.progress;
    }

    return QVariant();
}

QVariant CustomTransferModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case FileNameColumn:
            return "文件名";
        case TargetDeviceColumn:
            return "目标设备";
        case FileSizeColumn:
            return "文件大小";
        case ProgressColumn:
            return "传输进度";
        case StateColumn:
            return "传输状态";
        case CreateTimeColumn:
            return "加入时间";
        default:
            return QVariant();
        }
    }

    return QVariant();
}

void CustomTransferModel::addTransferFile(const TransferFileData &fileData)
{
    // 插入数据前发送信号，通知视图开始更新（Model/View 规范）
    beginInsertRows(QModelIndex(), m_transferFileList.count(), m_transferFileList.count());
    m_transferFileList.append(fileData);
    // 插入数据后发送信号，通知视图完成更新
    endInsertRows();
}

void CustomTransferModel::updateTransferProgress(const QString &fileName, const QString &targetDevice, qint64 transferredSize, TransferState state)
{
    // 遍历查找对应文件
    for (int i = 0; i < m_transferFileList.count(); ++i) {
        TransferFileData &fileData = const_cast<TransferFileData &>(m_transferFileList.at(i));
        if (fileData.fileName == fileName && fileData.targetDevice == targetDevice) {
            // 更新传输数据
            fileData.transferredSize = transferredSize;
            fileData.state = state;
            // 计算传输进度（避免除零错误）
            fileData.progress = fileData.fileSize > 0 ? (static_cast<float>(transferredSize) / fileData.fileSize) * 100 : 0.0f;

            // 通知视图指定单元格更新（高效，避免全表刷新）
            QModelIndex index = this->index(i, 0);
            emit dataChanged(index, this->index(i, ColumnCount - 1));
            break;
        }
    }
}

void CustomTransferModel::clearTransferQueue()
{
    beginResetModel();
    m_transferFileList.clear();
    endResetModel();
}

TransferFileData CustomTransferModel::getTransferFile(int row) const
{
    if (row >= 0 && row < m_transferFileList.count()) {
        return m_transferFileList.at(row);
    }
    return TransferFileData();
}

QString CustomTransferModel::stateToString(TransferState state) const
{
    switch (state) {
    case TransferWaiting:
        return "等待传输";
    case TransferRunning:
        return "传输中";
    case TransferPaused:
        return "已暂停";
    case TransferCompleted:
        return "传输完成";
    case TransferFailed:
        return "传输失败";
    default:
        return "未知状态";
    }
}

QString CustomTransferModel::fileSizeToString(qint64 fileSize) const
{
    const qint64 KB = 1024;
    const qint64 MB = KB * 1024;
    const qint64 GB = MB * 1024;

    if (fileSize >= GB) {
        return QString("%1 GB").arg(QString::number(static_cast<double>(fileSize) / GB, 'f', 2));
    } else if (fileSize >= MB) {
        return QString("%1 MB").arg(QString::number(static_cast<double>(fileSize) / MB, 'f', 2));
    } else if (fileSize >= KB) {
        return QString("%1 KB").arg(QString::number(static_cast<double>(fileSize) / KB, 'f', 2));
    } else {
        return QString("%1 B").arg(fileSize);
    }
}
