#include "registwidget.h"
#include "ui_registwidget.h"

registwidget::registwidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::registwidget)
{
    ui->setupUi(this);
}

registwidget::~registwidget()
{
    delete ui;
}

void registwidget::on_cancelbtn_clicked()
{
    emit cancelorreturnsig();
    close();
}


void registwidget::on_registbtn_clicked()
{
    QString name,username,password;
    if((name=ui->NamelineEdit->text()).isEmpty()||name.trimmed().isEmpty()){
        return;
    }
    if((username=ui->UseNamelineEdit->text()).isEmpty()||username.trimmed().isEmpty()){

        return;
    }
    if((password=ui->passwordlineEdit->text()).isEmpty()||password.trimmed().isEmpty()){

        return;
    }

    //提交注册信号
    emit registsig(name ,username,password);
    close();
}


void registwidget::on_returnbtn_clicked()
{
    emit cancelorreturnsig();
    close();
}

