#ifndef PATIENTMANAGERWIDGET_H
#define PATIENTMANAGERWIDGET_H

#include <QSqlTableModel>
#include <QWidget>

namespace Ui {
class patientManagerwidget;
}

class patientManagerwidget : public QWidget
{
    Q_OBJECT

public:
    explicit patientManagerwidget(QSqlDatabase *db,QWidget *parent = nullptr);
    ~patientManagerwidget();
signals:
    void returnlogin();

private slots:
    void on_returnbtn_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void handleaddpatient(QString name,QString cardId,QString sex,int age,QString birthday,double height,double weight,QString phone);

private:
    Ui::patientManagerwidget *ui;
    QSqlDatabase *m_db=nullptr;
    QSqlTableModel *m_model=nullptr;
};

#endif // PATIENTMANAGERWIDGET_H
