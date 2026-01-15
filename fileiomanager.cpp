// fileiomanager.cpp
#include "fileiomanager.h"
#include <QFileInfo>
#include <QDebug>

FileIoManager::FileIoManager(QObject *parent)
    : QObject(parent)
    , m_breakpointIniPath("./breakpoint_records.ini")
{
    // 初始化断点记录配置文件
    m_breakpointSettings = new QSettings(m_breakpointIniPath, QSettings::IniFormat, this);
}

QByteArray FileIoManager::readFileBlock(const QString &filePath, qint64 offset, qint64 blockSize)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "文件打开失败（读取）：" << filePath << file.errorString();
        return QByteArray();
    }

    // 移动到指定偏移量
    if (!file.seek(offset)) {
        qDebug() << "文件偏移失败（读取）：" << offset;
        file.close();
        return QByteArray();
    }

    // 读取块数据
    QByteArray blockData = file.read(blockSize);
    file.close();
    return blockData;
}

bool FileIoManager::writeFileBlock(const QString &filePath, const QByteArray &blockData, qint64 offset, bool append)
{
    QFile file(filePath);
    QIODevice::OpenMode openMode = QIODevice::WriteOnly;
    if (append) {
        openMode |= QIODevice::Append;
    }

    if (!file.open(openMode)) {
        qDebug() << "文件打开失败（写入）：" << filePath << file.errorString();
        return false;
    }

    // 移动到指定偏移量（覆盖模式下有效）
    if (!append && !file.seek(offset)) {
        qDebug() << "文件偏移失败（写入）：" << offset;
        file.close();
        return false;
    }

    // 写入块数据
    qint64 writtenSize = file.write(blockData);
    file.close();

    if (writtenSize != blockData.size()) {
        qDebug() << "文件写入不完整，预期：" << blockData.size() << "实际：" << writtenSize;
        return false;
    }

    return true;
}

qint64 FileIoManager::getFileSize(const QString &filePath)
{
    QFileInfo fileInfo(filePath);
    if (!fileInfo.exists() || !fileInfo.isFile()) {
        return -1;
    }
    return fileInfo.size();
}

qint64 FileIoManager::loadBreakpointOffset(const QString &fileName, const QString &targetDevice)
{
    QString key = QString("%1/%2").arg(targetDevice).arg(fileName);
    return m_breakpointSettings->value(key, 0).toLongLong();
}

bool FileIoManager::saveBreakpointOffset(const QString &fileName, const QString &targetDevice, qint64 offset)
{
    QString key = QString("%1/%2").arg(targetDevice).arg(fileName);
    m_breakpointSettings->setValue(key, offset);
    m_breakpointSettings->sync(); // 立即写入文件，避免数据丢失
    return true;
}

bool FileIoManager::deleteBreakpointRecord(const QString &fileName, const QString &targetDevice)
{
    QString key = QString("%1/%2").arg(targetDevice).arg(fileName);
    m_breakpointSettings->remove(key);
    m_breakpointSettings->sync();
    return true;
}
