// landevicediscoverer.h
#ifndef LANDEVICEDISCOVERER_H
#define LANDEVICEDISCOVERER_H

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>
#include <QTimer>
#include <QMap>

class LanDeviceDiscoverer : public QObject
{
    Q_OBJECT
public:
    explicit LanDeviceDiscoverer(QObject *parent = nullptr);
    ~LanDeviceDiscoverer() override;

    // 启动设备发现（广播 + 监听）
    bool startDiscover();
    // 停止设备发现
    void stopDiscover();
    // 获取在线设备列表（设备名 -> IP 地址）
    QMap<QString, QString> getOnlineDevices() const;

signals:
    // 设备列表更新信号（传递给主线程更新界面）
    void onlineDevicesUpdated(const QMap<QString, QString> &devices);

private slots:
    // 发送广播消息
    void sendBroadcastMessage();
    // 接收广播响应
    void onReadyRead();
    // 清理离线设备（超时未响应）
    void cleanOfflineDevices();

private:
    QUdpSocket *m_udpSocket;       // UDP 套接字
    QTimer *m_broadcastTimer;      // 广播定时器（定时发送发现消息）
    QTimer *m_cleanDeviceTimer;    // 设备清理定时器
    QMap<QString, qint64> m_deviceLastActive; // 设备最后活跃时间（设备IP -> 时间戳）
    QMap<QString, QString> m_onlineDevices;   // 在线设备列表
    QString m_localDeviceName;     // 本地设备名
    QString m_localIpAddress;      // 本地 IP 地址

    // 辅助函数：获取本地 IP 地址（局域网）
    QString getLocalIpAddress() const;
};

#endif // LANDEVICEDISCOVERER_H
