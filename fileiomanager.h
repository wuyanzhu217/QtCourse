// fileiomanager.h
#ifndef FILEIOMANAGER_H
#define FILEIOMANAGER_H

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QFile>
#include <QSettings>

class FileIoManager : public QObject
{
    Q_OBJECT
public:
    explicit FileIoManager(QObject *parent = nullptr);

    // 读取文件指定偏移量的块数据
    QByteArray readFileBlock(const QString &filePath, qint64 offset, qint64 blockSize);
    // 写入文件块数据到指定路径（支持追加/覆盖）
    bool writeFileBlock(const QString &filePath, const QByteArray &blockData, qint64 offset, bool append = true);
    // 获取文件大小
    qint64 getFileSize(const QString &filePath);
    // 加载断点续传偏移量
    qint64 loadBreakpointOffset(const QString &fileName, const QString &targetDevice);
    // 保存断点续传偏移量
    bool saveBreakpointOffset(const QString &fileName, const QString &targetDevice, qint64 offset);
    // 删除断点续传记录
    bool deleteBreakpointRecord(const QString &fileName, const QString &targetDevice);

private:
    QSettings *m_breakpointSettings;  // 用于保存断点续传信息（ini 文件）
    QString m_breakpointIniPath;      // 断点记录文件路径
};

#endif // FILEIOMANAGER_H
