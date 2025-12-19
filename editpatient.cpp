#include "editpatient.h"
#include "ui_editpatient.h"

editPatient::editPatient(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::editPatient)
{
    ui->setupUi(this);
}

editPatient::~editPatient()
{
    delete ui;
}

void editPatient::on_pushButton_clicked()
{
    QString name=ui->nameline->text();
    QString cardId=ui->cardIdline->text();
    QString sex=ui->sexcombox->currentText();
    int age=QDate::currentDate().year()-ui->dateEdit->date().year();
    double height=ui->heightspinBox->cleanText().toDouble();
    double weight=ui->weigthspinBox->cleanText().toDouble();
    QString phone=ui->phonelineEdit->text();

    emit addpatientsig(name,cardId,sex,age,ui->dateEdit->date().toString(),height,weight,phone);
    close();
}


void editPatient::on_pushButton_2_clicked()
{
    emit returnpatientwidget();
    close();
}


void editPatient::on_pushButton_5_clicked()
{
    emit returnpatientwidget();
    close();
}

