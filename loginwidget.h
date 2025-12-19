#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include "patientmanagerwidget.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QWidget>

namespace Ui {
class loginwidget;
}

class loginwidget : public QWidget
{
    Q_OBJECT

public:
    explicit loginwidget(QSqlDatabase *_db,QWidget *parent = nullptr);
    ~loginwidget();

signals:
    void returnmain();
private slots:

    void on_patientbtn_clicked();

    void on_returnbtn_clicked();

private:
    Ui::loginwidget *ui;
    QSqlDatabase *m_db=nullptr;
    QSqlQuery *query=nullptr;
    patientManagerwidget* patientwid=nullptr;
};

#endif // LOGINWIDGET_H
