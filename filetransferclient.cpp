// filetransferclient.cpp
#include "filetransferclient.h"
#include <QDataStream>
#include <QDebug>

FileTransferClient::FileTransferClient(QObject *parent)
    : QObject(parent)
    , m_tcpSocket(new QTcpSocket(this))
{
    // 连接连接状态变化信号
    connect(m_tcpSocket, &QTcpSocket::connected, this, [=]() {
        emit connectionStateChanged(true);
    });

    connect(m_tcpSocket, &QTcpSocket::disconnected, this, [=]() {
        emit connectionStateChanged(false);
    });
}

FileTransferClient::~FileTransferClient()
{
    disconnectFromServer();
}

bool FileTransferClient::connectToServer(const QString &serverIp, quint16 serverPort)
{
    if (m_tcpSocket->state() == QTcpSocket::ConnectedState) {
        return true;
    }

    // 连接 TCP 服务器
    m_tcpSocket->connectToHost(serverIp, 9901);
    // 等待连接完成（超时 5 秒）
    if (!m_tcpSocket->waitForConnected(5000)) {
        qDebug() << "TCP 连接超时：" << serverIp << ":" << serverPort;
        return false;
    }

    return true;
}

void FileTransferClient::disconnectFromServer()
{
    if (m_tcpSocket->state() != QTcpSocket::UnconnectedState) {
        m_tcpSocket->disconnectFromHost();
        m_tcpSocket->waitForDisconnected(1000);
    }
}

bool FileTransferClient::sendFileHeader(const QString &fileName, qint64 fileSize, qint64 breakpointOffset)
{
    if (m_tcpSocket->state() != QTcpSocket::ConnectedState) {
        return false;
    }

    // 构造文件头数据（使用 QDataStream 序列化，保证数据一致性）
    QByteArray headerData;
    QDataStream out(&headerData, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_15);

    out << fileName;
    out << fileSize;
    out << breakpointOffset;

    // 发送文件头（先发送头数据长度，再发送头数据）
    qint64 headerSize = headerData.size();
    m_tcpSocket->write(reinterpret_cast<const char *>(&headerSize), sizeof(qint64));
    m_tcpSocket->write(headerData);

    // 等待数据发送完成
    return m_tcpSocket->waitForBytesWritten(3000);
}

bool FileTransferClient::sendFileBlock(const QByteArray &blockData)
{
    if (m_tcpSocket->state() != QTcpSocket::ConnectedState || blockData.isEmpty()) {
        return false;
    }

    // 发送文件块数据
    qint64 writtenSize = m_tcpSocket->write(blockData);
    if (writtenSize != blockData.size()) {
        return false;
    }

    // 等待数据发送完成（非阻塞，可根据需求调整）
    m_tcpSocket->waitForBytesWritten(100);
    return true;
}
