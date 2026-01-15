// landevicediscoverer.cpp
#include "landevicediscoverer.h"
#include <QHostInfo>
#include <QNetworkInterface>
#include <QDateTime>
#include <QDebug>

LanDeviceDiscoverer::LanDeviceDiscoverer(QObject *parent)
    : QObject(parent)
    , m_udpSocket(nullptr)
    , m_broadcastTimer(nullptr)
    , m_cleanDeviceTimer(nullptr)
    , m_localDeviceName(QHostInfo::localHostName())
    , m_localIpAddress(getLocalIpAddress())
{
}

LanDeviceDiscoverer::~LanDeviceDiscoverer()
{
    stopDiscover();
}

bool LanDeviceDiscoverer::startDiscover()
{
    // 初始化 UDP 套接字
    m_udpSocket = new QUdpSocket(this);
    if (!m_udpSocket->bind(LAN_BROADCAST_PORT, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint)) {
        qDebug() << "UDP 绑定端口失败：" << LAN_BROADCAST_PORT;
        delete m_udpSocket;
        m_udpSocket = nullptr;
        return false;
    }

    // 连接信号槽
    connect(m_udpSocket, &QUdpSocket::readyRead, this, &LanDeviceDiscoverer::onReadyRead);

    // 初始化广播定时器（每 3 秒发送一次广播）
    m_broadcastTimer = new QTimer(this);
    m_broadcastTimer->setInterval(3000);
    connect(m_broadcastTimer, &QTimer::timeout, this, &LanDeviceDiscoverer::sendBroadcastMessage);

    // 初始化设备清理定时器（每 10 秒清理一次离线设备）
    m_cleanDeviceTimer = new QTimer(this);
    m_cleanDeviceTimer->setInterval(10000);
    connect(m_cleanDeviceTimer, &QTimer::timeout, this, &LanDeviceDiscoverer::cleanOfflineDevices);

    // 启动定时器
    m_broadcastTimer->start();
    m_cleanDeviceTimer->start();

    // 立即发送一次广播
    sendBroadcastMessage();

    qDebug() << "局域网设备发现已启动，本地 IP：" << m_localIpAddress;
    return true;
}

void LanDeviceDiscoverer::stopDiscover()
{
    if (m_broadcastTimer) {
        m_broadcastTimer->stop();
        delete m_broadcastTimer;
        m_broadcastTimer = nullptr;
    }

    if (m_cleanDeviceTimer) {
        m_cleanDeviceTimer->stop();
        delete m_cleanDeviceTimer;
        m_cleanDeviceTimer = nullptr;
    }

    if (m_udpSocket) {
        m_udpSocket->close();
        delete m_udpSocket;
        m_udpSocket = nullptr;
    }

    m_onlineDevices.clear();
    m_deviceLastActive.clear();
    emit onlineDevicesUpdated(m_onlineDevices);
}

QMap<QString, QString> LanDeviceDiscoverer::getOnlineDevices() const
{
    return m_onlineDevices;
}

void LanDeviceDiscoverer::sendBroadcastMessage()
{
    if (!m_udpSocket) {
        return;
    }

    // 构造广播消息（设备名|IP 地址）
    QString broadcastMsg = QString("%1|%2").arg(m_localDeviceName).arg(m_localIpAddress);
    QByteArray data = broadcastMsg.toUtf8();

    // 发送 UDP 广播到局域网（255.255.255.255）
    m_udpSocket->writeDatagram(data, QHostAddress::Broadcast, LAN_BROADCAST_PORT);
}

void LanDeviceDiscoverer::onReadyRead()
{
    if (!m_udpSocket) {
        return;
    }

    while (m_udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(m_udpSocket->pendingDatagramSize());
        QHostAddress senderAddr;
        quint16 senderPort;

        // 读取数据报
        m_udpSocket->readDatagram(datagram.data(), datagram.size(), &senderAddr, &senderPort);
        QString senderIp = senderAddr.toString();

        // 忽略本地设备消息
        if (senderIp == m_localIpAddress || senderIp == "127.0.0.1") {
            continue;
        }

        // 解析消息（设备名|IP 地址）
        QString msg = QString::fromUtf8(datagram);
        QStringList msgParts = msg.split("|");
        if (msgParts.count() != 2) {
            continue;
        }

        QString deviceName = msgParts[0];
        QString deviceIp = msgParts[1];

        // 更新设备最后活跃时间
        qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
        m_deviceLastActive[deviceIp] = currentTime;

        // 更新在线设备列表
        if (!m_onlineDevices.contains(deviceName) || m_onlineDevices[deviceName] != deviceIp) {
            m_onlineDevices[deviceName] = deviceIp;
            emit onlineDevicesUpdated(m_onlineDevices);
        }
    }
}

void LanDeviceDiscoverer::cleanOfflineDevices()
{
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
    qint64 timeout = 15000; // 15 秒超时未响应视为离线

    QList<QString> offlineDeviceIps;
    for (auto it = m_deviceLastActive.constBegin(); it != m_deviceLastActive.constEnd(); ++it) {
        if (currentTime - it.value() > timeout) {
            offlineDeviceIps.append(it.key());
        }
    }

    // 移除离线设备
    for (const QString &ip : offlineDeviceIps) {
        m_deviceLastActive.remove(ip);

        // 从在线设备列表中移除
        QList<QString> deviceNamesToRemove;
        for (auto it = m_onlineDevices.constBegin(); it != m_onlineDevices.constEnd(); ++it) {
            if (it.value() == ip) {
                deviceNamesToRemove.append(it.key());
            }
        }

        for (const QString &name : deviceNamesToRemove) {
            m_onlineDevices.remove(name);
        }
    }

    // 发送设备列表更新信号
    if (!offlineDeviceIps.isEmpty()) {
        emit onlineDevicesUpdated(m_onlineDevices);
    }
}

QString LanDeviceDiscoverer::getLocalIpAddress() const
{
    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
    for (const QNetworkInterface &iface : interfaces) {
        // 忽略回环接口和禁用的接口
        if (iface.flags() & QNetworkInterface::IsLoopBack || !(iface.flags() & QNetworkInterface::IsUp)) {
            continue;
        }

        QList<QNetworkAddressEntry> entries = iface.addressEntries();
        for (const QNetworkAddressEntry &entry : entries) {
            // 只返回 IPv4 局域网地址
            if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol &&
                    !entry.ip().isLoopback() &&
                    entry.ip().toString().startsWith("192.168.") ||
                entry.ip().toString().startsWith("10.") ||
                entry.ip().toString().startsWith("172.")) {
                return entry.ip().toString();
            }
        }
    }

    return "127.0.0.1";
}
