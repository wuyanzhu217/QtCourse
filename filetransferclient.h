// filetransferclient.h
#ifndef FILETRANSFERCLIENT_H
#define FILETRANSFERCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QString>

class FileTransferClient : public QObject
{
    Q_OBJECT
public:
    explicit FileTransferClient(QObject *parent = nullptr);
    ~FileTransferClient() override;

    // 连接目标设备 TCP 服务器
    bool connectToServer(const QString &serverIp, quint16 serverPort);
    // 断开与服务器的连接
    void disconnectFromServer();
    // 发送文件头信息（文件名、文件大小、断点偏移量）
    bool sendFileHeader(const QString &fileName, qint64 fileSize, qint64 breakpointOffset);
    // 发送文件块数据
    bool sendFileBlock(const QByteArray &blockData);

signals:
    // 连接状态变化信号
    void connectionStateChanged(bool isConnected);

private:
    QTcpSocket *m_tcpSocket; // TCP 套接字
};

#endif // FILETRANSFERCLIENT_H
