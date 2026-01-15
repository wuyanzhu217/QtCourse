#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMap>
#include <QFileInfo>
#include <QMessageBox>
#include <QFileDialog>

// 引入所有核心模块头文件
#include "landevicediscoverer.h"
#include "customtransfermodel.h"
#include "transferqueuemanager.h"
#include "transferworkerthread.h"
#include "fileiomanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT  // 必须保留，支持信号槽机制

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    // 1. 设备发现相关槽函数
    void onOnlineDevicesUpdated(const QMap<QString, QString> &devices);

    // 2. 文件传输相关槽函数
    void onSelectFilesClicked();       // 选择待传输文件
    void onStartTransferClicked();     // 启动传输
    void onPauseTransferClicked();     // 暂停传输
    void onCancelTransferClicked();    // 取消传输
    void onClearQueueClicked();        // 清空传输队列

    // 3. 传输结果回调槽函数
    void onTransferFinished(const QString &fileName, const QString &targetDevice, bool isSuccess);

private:
    // 1. UI 指针
    Ui::Widget *ui;

    // 2. 核心模块成员变量（整合所有功能模块）
    LanDeviceDiscoverer *m_lanDeviceDiscoverer;        // 局域网设备发现模块
    CustomTransferModel *m_customTransferModel;        // 自定义 Model/View 模块
    TransferQueueManager *m_transferQueueManager;      // 传输队列管理模块
    TransferWorkerThread *m_transferWorkerThread;      // 后台传输线程模块
    FileIoManager *m_fileIoManager;                    // 文件 I/O 辅助模块

    // 3. 辅助函数（私有化，内部调用）
    void initUiAndModel();            // 初始化 UI 与 Model/View 绑定
    void initModuleConnections();     // 初始化所有模块的信号槽连接
    void startNextPendingTask();      // 启动队列中的下一个待传输任务
};

#endif // WIDGET_H
