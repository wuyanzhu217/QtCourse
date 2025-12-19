#include "loginwidget.h"
#include "ui_loginwidget.h"

loginwidget::loginwidget(QSqlDatabase *_db,QWidget *parent)
    : QWidget(parent),m_db(_db)
    , ui(new Ui::loginwidget)
{
    ui->setupUi(this);
    query=new QSqlQuery(*_db);
}

loginwidget::~loginwidget()
{
    delete ui;
    if(patientwid){
        delete patientwid;
        patientwid=nullptr;
    }
    if(query){
        delete query;
        query=nullptr;
    }
}

void loginwidget::on_patientbtn_clicked()
{
    if(!patientwid) patientwid=new patientManagerwidget(m_db);
    connect(patientwid,&patientManagerwidget::returnlogin,this,[=](){
        show();
    });
    patientwid->show();
    close();
}


void loginwidget::on_returnbtn_clicked()
{
    close();
    emit returnmain();

}

