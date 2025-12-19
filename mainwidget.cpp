#include "mainwidget.h"
#include "registwidget.h"
#include "ui_mainwidget.h"

#include <QSqlQuery>
#include <QSqlError>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    if(!QSqlDatabase::isDriverAvailable("QSQLITE")){
        qDebug()<<"数据库驱动不可用";
    }
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("test.db");

    //打开sqlite数据库
    if(m_db.open()){
        qDebug()<<"连接数据库成功";
        query = new QSqlQuery(m_db);
    }
    else{
        qDebug()<<"连接数据库失败";
    }
}

Widget::~Widget()
{
    delete ui;
    if(registwid) { delete registwid; registwid=nullptr;}
    if(loginwid) {delete loginwid; loginwid=nullptr;}
}

void Widget::on_registbtn_clicked()
{

    if(m_db.isOpen()){
        if(!registwid)registwid=new registwidget();
        connect(registwid,&registwidget::registsig,this,&Widget::handleregist);
        connect(registwid,&registwidget::cancelorreturnsig,this,[=](){
            show();
        });
        registwid->show();
        hide();
    }
    else{

    }
}

void Widget::handleregist(QString name, QString username, QString password)
{
    if(m_db.isOpen()){
        //qDebug()<<name<<username<<password;
        query->prepare("INSERT INTO User(FULLNAME,USERNAME,PASSWORD) VALUES(:name, :username, :password)");
        query->bindValue(":name",name);
        query->bindValue(":username",username);
        query->bindValue(":password",password);

        if(!query->exec()){
            qDebug()<<"语句错误，执行sql失败！";
            qDebug()<<"sql:"<<query->lastQuery()<<",result:"<<query->lastError().text();
            return;
        }
        else{

        }
    }
    this->show();
}


void Widget::on_loginbtn_clicked()
{
    QString username,password;
    if((username=ui->UseNamelineEdit->text()).isEmpty()){

        return;
    }
    if((password=ui->passwordlineEdit->text()).isEmpty()){

        return;
    }


    query->prepare("select *from User where USERNAME= :username");
    query->bindValue(":username",username);
    if(!query->exec()){
        qDebug()<<"语句错误，执行sql失败！";
        qDebug()<<"sql:"<<query->lastQuery();
        return;
    }
    if(query->next()){
        if(query->value("PASSWORD").toString()==password){

            //切换到登录成功页面
            if(!loginwid) loginwid=new loginwidget(&m_db);
            connect(loginwid,&loginwidget::returnmain,this,[=](){
                show();
            });
            loginwid->show();
            this->hide();
        }
    }
}

