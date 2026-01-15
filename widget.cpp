#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    // 实例化所有核心模块（父对象传递 this，利用 Qt 父子对象机制自动释放资源）
    , m_lanDeviceDiscoverer(new LanDeviceDiscoverer(this))
    , m_customTransferModel(new CustomTransferModel(this))
    , m_transferQueueManager(new TransferQueueManager(this))
    , m_transferWorkerThread(new TransferWorkerThread(this))
    , m_fileIoManager(new FileIoManager(this))
{
    ui->setupUi(this);

    // 1. 初始化 UI 与 Model/View 绑定
    initUiAndModel();

    // 2. 初始化所有模块的信号槽连接（线程安全）
    initModuleConnections();

    // 3. 启动局域网设备发现（核心模块启动）
    if (!m_lanDeviceDiscoverer->startDiscover()) {
        QMessageBox::warning(this, "初始化警告", "局域网设备发现模块启动失败！\n请检查网络端口是否被占用。");
    }

    // 4. 设置窗体标题
    this->setWindowTitle("Qt6 局域网文件传输与共享系统");
}

Widget::~Widget()
{
    // 1. 安全停止后台传输线程（避免内存泄漏与资源占用）
    if (m_transferWorkerThread->isRunning()) {
        m_transferWorkerThread->cancelTransfer();
        m_transferWorkerThread->quit();
        m_transferWorkerThread->wait(5000);  // 等待 5 秒，确保线程正常退出
    }

    // 2. 停止局域网设备发现
    m_lanDeviceDiscoverer->stopDiscover();

    // 3. 释放 UI 资源（Qt 父子对象机制自动释放其他模块）
    delete ui;
}

// ---------------------- 私有辅助函数实现 ----------------------
void Widget::initUiAndModel()
{
    // 1. 绑定 CustomTransferModel 到 QTableView（Model/View 核心绑定）
    ui->tableView_transfer->setModel(m_customTransferModel);

    // 2. 配置 QTableView 样式（自适应列宽、拉伸最后一列）
    ui->tableView_transfer->horizontalHeader()->setStretchLastSection(true);
    ui->tableView_transfer->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView_transfer->setSelectionBehavior(QAbstractItemView::SelectRows);  // 整行选择
    ui->tableView_transfer->setEditTriggers(QAbstractItemView::NoEditTriggers);   // 禁止编辑单元格

    // 3. 初始化按钮状态（默认暂停、取消按钮不可用）
    ui->btn_pause_transfer->setEnabled(false);
    ui->btn_cancel_transfer->setEnabled(false);
}

void Widget::initModuleConnections()
{
    // 1. 设备发现模块：在线设备更新信号 -> 窗体槽函数
    connect(m_lanDeviceDiscoverer, &LanDeviceDiscoverer::onlineDevicesUpdated,
            this, &Widget::onOnlineDevicesUpdated, Qt::QueuedConnection);  // 队列连接，线程安全

    // 2. 后台传输线程：进度更新信号 -> Model 刷新信号（直接绑定，线程安全）
    connect(m_transferWorkerThread, &TransferWorkerThread::transferProgressUpdated,
            m_customTransferModel, &CustomTransferModel::updateTransferProgress, Qt::QueuedConnection);

    // 3. 后台传输线程：传输完成/失败信号 -> 窗体槽函数
    connect(m_transferWorkerThread, &TransferWorkerThread::transferFinished,
            this, &Widget::onTransferFinished, Qt::QueuedConnection);

    // 4. UI 按钮：绑定点击信号到对应槽函数（可视化设计的按钮，需确保 ui 中对象名一致）
    connect(ui->btn_select_files, &QPushButton::clicked, this, &Widget::onSelectFilesClicked);
    connect(ui->btn_start_transfer, &QPushButton::clicked, this, &Widget::onStartTransferClicked);
    connect(ui->btn_pause_transfer, &QPushButton::clicked, this, &Widget::onPauseTransferClicked);
    connect(ui->btn_cancel_transfer, &QPushButton::clicked, this, &Widget::onCancelTransferClicked);
    connect(ui->btn_clear_queue, &QPushButton::clicked, this, &Widget::onClearQueueClicked);
}

void Widget::startNextPendingTask()
{
    // 从队列中获取第一个待传输任务
    TransferFileData pendingTask = m_transferQueueManager->getFirstPendingTask();
    if (pendingTask.fileName.isEmpty()) {
        // 队列为空，重置按钮状态
        ui->btn_start_transfer->setEnabled(true);
        ui->btn_pause_transfer->setEnabled(false);
        ui->btn_cancel_transfer->setEnabled(false);
        QMessageBox::information(this, "传输提示", "传输队列为空，已停止自动续传。");
        return;
    }

    // 配置并启动后台传输任务
    m_transferWorkerThread->setTransferTask(pendingTask, "./ReceivedFiles/");
    if (!m_transferWorkerThread->isRunning()) {
        m_transferWorkerThread->start();  // 启动线程（首次运行）
    } else {
        m_transferWorkerThread->resumeTransfer();  // 恢复线程（暂停后继续）
    }

    // 更新按钮状态
    ui->btn_start_transfer->setEnabled(false);
    ui->btn_pause_transfer->setEnabled(true);
    ui->btn_cancel_transfer->setEnabled(true);
}

// ---------------------- 槽函数实现 ----------------------
void Widget::onOnlineDevicesUpdated(const QMap<QString, QString> &devices)
{
    // 清空目标设备下拉框（先保存当前选中项）
    QString currentSelected = ui->combo_target_device->currentText();  // 修正：label → combo
    ui->combo_target_device->clear();  // 修正：label → combo

    // 添加在线设备到下拉框（格式：设备名（IP地址））
    ui->combo_target_device->addItem("请选择目标设备", "");  // 修正1：label → combo；修正2：补充缺失的 addItem 调用（原代码少了函数名）
    for (auto it = devices.constBegin(); it != devices.constEnd(); ++it) {
        QString deviceText = QString("%1 (%2)").arg(it.key()).arg(it.value());
        ui->combo_target_device->addItem(deviceText, it.value());  // 修正：label → combo
    }

    // 恢复之前的选中项（若存在）
    int index = ui->combo_target_device->findText(currentSelected);  // 修正：label → combo
    if (index != -1) {
        ui->combo_target_device->setCurrentIndex(index);  // 修正：label → combo
    }
}

void Widget::onSelectFilesClicked()
{
    // 打开文件对话框，支持多文件选择
    QStringList filePaths = QFileDialog::getOpenFileNames(this, "选择待传输文件",
                                                          QDir::homePath(), "所有文件 (*.*)");
    if (filePaths.isEmpty()) {
        return;
    }

    // 获取选中的目标设备 IP（修正：label → combo）
    QString targetDeviceIp = ui->combo_target_device->currentData().toString();
    if (targetDeviceIp.isEmpty()) {
        QMessageBox::warning(this, "选择警告", "请先从下拉框选择有效的目标设备！");
        return;
    }

    // 批量构造传输文件数据，添加到 Model 与传输队列
    for (const QString &filePath : filePaths) {
        QFileInfo fileInfo(filePath);
        if (!fileInfo.exists() || !fileInfo.isFile()) {
            QMessageBox::warning(this, "文件警告", QString("文件 %1 无效，跳过该文件。").arg(filePath));
            continue;
        }

        // 构造 TransferFileData 结构体
        TransferFileData fileData;
        fileData.fileName = fileInfo.fileName();
        fileData.filePath = filePath;
        fileData.targetDevice = targetDeviceIp;
        fileData.fileSize = fileInfo.size();
        fileData.transferredSize = 0;
        fileData.state = TransferWaiting;
        fileData.createTime = QDateTime::currentDateTime();
        fileData.progress = 0.0f;

        // 添加到 Model（更新界面）与传输队列（后台管理）
        m_customTransferModel->addTransferFile(fileData);
        m_transferQueueManager->addTaskToQueue(fileData);
    }

    QMessageBox::information(this, "添加成功", QString("已成功添加 %1 个文件到传输队列。").arg(filePaths.size()));
}
void Widget::onStartTransferClicked()
{
    // 检查传输队列是否为空
    if (m_transferQueueManager->getQueueCount() == 0) {
        QMessageBox::warning(this, "启动警告", "传输队列为空，请先添加待传输文件！");
        return;
    }

    // 启动下一个待传输任务
    startNextPendingTask();
}

void Widget::onPauseTransferClicked()
{
    // 暂停后台传输线程
    m_transferWorkerThread->pauseTransfer();

    // 更新按钮状态
    ui->btn_pause_transfer->setEnabled(false);
    ui->btn_start_transfer->setEnabled(true);
    QMessageBox::information(this, "传输提示", "文件传输已暂停，可点击「开始传输」恢复。");
}

void Widget::onCancelTransferClicked()
{
    // 确认是否取消传输
    int ret = QMessageBox::question(this, "取消确认", "确定要取消当前文件传输吗？已传输部分将保存断点，可后续续传。",
                                    QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if (ret != QMessageBox::Yes) {
        return;
    }

    // 取消后台传输线程
    m_transferWorkerThread->cancelTransfer();

    // 更新按钮状态
    ui->btn_pause_transfer->setEnabled(false);
    ui->btn_cancel_transfer->setEnabled(false);
    ui->btn_start_transfer->setEnabled(true);
}

void Widget::onClearQueueClicked()
{
    // 确认是否清空队列
    int ret = QMessageBox::question(this, "清空确认", "确定要清空传输队列吗？已完成的传输记录将保留，未传输任务将被删除。",
                                    QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if (ret != QMessageBox::Yes) {
        return;
    }

    // 清空传输队列与 Model 数据
    m_customTransferModel->clearTransferQueue();
    m_transferQueueManager->clearQueue();

    // 若当前正在传输，取消传输
    if (m_transferWorkerThread->isRunning()) {
        m_transferWorkerThread->cancelTransfer();
    }

    // 更新按钮状态
    ui->btn_pause_transfer->setEnabled(false);
    ui->btn_cancel_transfer->setEnabled(false);
    ui->btn_start_transfer->setEnabled(true);

    QMessageBox::information(this, "清空提示", "传输队列已成功清空。");
}

void Widget::onTransferFinished(const QString &fileName, const QString &targetDevice, bool isSuccess)
{
    // 显示传输结果
    if (isSuccess) {
        QMessageBox::information(this, "传输成功", QString("文件 %1 已成功传输到目标设备 %2。").arg(fileName).arg(targetDevice));
    } else {
        QMessageBox::warning(this, "传输失败", QString("文件 %1 传输失败！\n已保存断点，可后续重新尝试传输。").arg(fileName));
    }

    // 从传输队列中移除已完成/失败的任务
    m_transferQueueManager->removeTaskFromQueue(fileName, targetDevice);

    // 自动启动下一个待传输任务（可选功能，提升用户体验）
    startNextPendingTask();
}
