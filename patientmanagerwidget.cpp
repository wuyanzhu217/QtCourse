#include "editpatient.h"
#include "patientmanagerwidget.h"
#include "ui_patientmanagerwidget.h"

#include<QMessageBox>

patientManagerwidget::patientManagerwidget(QSqlDatabase *db,QWidget *parent)
    : QWidget(parent),m_db(db)
    , ui(new Ui::patientManagerwidget)
{
    ui->setupUi(this);
    m_model = new QSqlTableModel(this,*db);
    m_model->setTable("Patient");
    m_model->setEditStrategy(QSqlTableModel::OnFieldChange);


    // 逐个设置表头显示文本（索引对应表字段顺序）
    m_model->setHeaderData(0, Qt::Horizontal, "ID");                  // 第0列：ID
    m_model->setHeaderData(1, Qt::Horizontal, "身份证号");            // 第1列：ID_CARD
    m_model->setHeaderData(2, Qt::Horizontal, "姓名");                // 第2列：NAME
    m_model->setHeaderData(3, Qt::Horizontal, "性别");                // 第3列：SEX
    m_model->setHeaderData(4, Qt::Horizontal, "出生日期");            // 第4列：DOB
    m_model->setHeaderData(5, Qt::Horizontal, "身高(cm)");            // 第5列：HEIGHT
    m_model->setHeaderData(6, Qt::Horizontal, "体重(kg)");            // 第6列：WEIGHT
    m_model->setHeaderData(7, Qt::Horizontal, "手机号");              // 第7列：MOBILEPHONE
    m_model->setHeaderData(8, Qt::Horizontal, "年龄");                // 第8列：AGE
    m_model->setHeaderData(9, Qt::Horizontal, "创建时间");            // 第9列：CREATEDTIMESTAMP
    m_model->select();

    ui->tableView->setModel(m_model);
    ui->tableView->resizeColumnsToContents();
}

patientManagerwidget::~patientManagerwidget()
{
    delete ui;
}

void patientManagerwidget::on_returnbtn_clicked()
{
    emit returnlogin();
    close();
}


void patientManagerwidget::on_pushButton_clicked()
{
    QString name = ui->lineEdit->text().trimmed();
    if (name.isEmpty()) {
        m_model->setFilter(""); // 清空过滤，显示所有数据
    } else {
        // 模糊查询：NAME包含输入的内容
        m_model->setFilter(QString("NAME LIKE '%%1%'").arg(name));
    }
    m_model->select(); // 重新查询生效
}


void patientManagerwidget::on_pushButton_2_clicked()
{
    editPatient *editpatienwidget=new editPatient();
    //hide();
    connect(editpatienwidget,&editPatient::addpatientsig,this,&patientManagerwidget::handleaddpatient);
    connect(editpatienwidget,&editPatient::returnpatientwidget,this,[=](){
        show();
    });
    editpatienwidget->show();
    hide();
}


void patientManagerwidget::on_pushButton_3_clicked()
{
    // 获取选中行
    QModelIndexList selectedRows = ui->tableView->selectionModel()->selectedRows();
    if (selectedRows.isEmpty()) {
        QMessageBox::warning(this, "提示", "请选择要删除的行");
        return;
    }

    // 从后往前删除（避免索引错位）
    for (auto it = selectedRows.rbegin(); it != selectedRows.rend(); ++it) {
        m_model->removeRow(it->row());
    }

    // 提交删除（也可以放到“保存修改”按钮统一提交）
    if (m_model->submitAll()) {
        QMessageBox::information(this, "成功", "选中数据已删除");
    }
}


void patientManagerwidget::on_pushButton_4_clicked()
{
    if (m_model->submitAll()) { // 提交所有修改到数据库
        QMessageBox::information(this, "成功", "数据已保存");
    } else {
        QMessageBox::critical(this, "失败","修改失败");
        m_model->revertAll(); // 回滚未提交的修改
    }
}

void patientManagerwidget::handleaddpatient(QString name, QString cardId, QString sex, int age, QString birthday,double height, double weight, QString phone)
{
    int row=m_model->rowCount();
    m_model->insertRow(row);
    m_model->setData(m_model->index(row,2),name);
    m_model->setData(m_model->index(row,1),cardId);
    m_model->setData(m_model->index(row,3),sex);
    m_model->setData(m_model->index(row,4),birthday);
    m_model->setData(m_model->index(row,5),height);
    m_model->setData(m_model->index(row,6),weight);
    m_model->setData(m_model->index(row,7),phone);
    m_model->setData(m_model->index(row,8),age);

    ui->tableView->scrollTo(m_model->index(row, 0));
    ui->tableView->setCurrentIndex(m_model->index(row, 2));
    show();
}

