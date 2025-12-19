#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "loginwidget.h"
#include "registwidget.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_registbtn_clicked();
    void handleregist(QString name,QString username,QString password);
    void on_loginbtn_clicked();

private:
    Ui::Widget *ui;
    QSqlDatabase m_db;
    QSqlQuery *query=nullptr;
    registwidget *registwid=nullptr;
    loginwidget *loginwid=nullptr;
};
#endif // MAINWIDGET_H
