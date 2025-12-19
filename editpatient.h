#ifndef EDITPATIENT_H
#define EDITPATIENT_H

#include <QWidget>

namespace Ui {
class editPatient;
}

class editPatient : public QWidget
{
    Q_OBJECT

public:
    explicit editPatient(QWidget *parent = nullptr);
    ~editPatient();
signals:
    void addpatientsig(QString name,QString cardId,QString sex,int age,QString birthday,double height,double weight,QString phone);
    void returnpatientwidget();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::editPatient *ui;
};

#endif // EDITPATIENT_H
