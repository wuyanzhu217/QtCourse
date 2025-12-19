#ifndef REGISTWIDGET_H
#define REGISTWIDGET_H

#include <QWidget>

namespace Ui {
class registwidget;
}

class registwidget : public QWidget
{
    Q_OBJECT

public:
    explicit registwidget(QWidget *parent = nullptr);
    ~registwidget();
signals:
    void registsig(QString name,QString username,QString password);
    void cancelorreturnsig();
private slots:
    void on_cancelbtn_clicked();
    void on_registbtn_clicked();

    void on_returnbtn_clicked();

private:
    Ui::registwidget *ui;

};

#endif // REGISTWIDGET_H
