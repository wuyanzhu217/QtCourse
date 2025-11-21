#include "searchdialog.h"
#include "ui_searchdialog.h"  // 确保包含正确的头文件
#include <QMessageBox>

SearchDialog::SearchDialog(QWidget *parent, QPlainTextEdit *textEdit)
    : QDialog(parent)
    , ui(new Ui::SearchDialog)  // 修改：searchDialog → SearchDialog
{
    ui->setupUi(this);

    pTextEdit = textEdit;
    ui->rbDown->setChecked(true);  // 修改：setCheckable(true) → setChecked(true)
}

SearchDialog::~SearchDialog()
{
    delete ui;
}

void SearchDialog::on_btFindNext_clicked()  // 修改：btnFindNext → btFindNext
{
    // 修改：searchtext → lineEdit
    QString target = ui->lineEdit->text();

    if(target == "" || pTextEdit == nullptr){
        return;
    }
    QString text = pTextEdit->toPlainText();

    QTextCursor c = pTextEdit->textCursor();
    int index = -1;

    // 修改：cbClass → checkBox
    if(ui->rbDown->isChecked()){
        index = text.indexOf(target, c.position(), ui->checkBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);
        if(index >= 0){
            c.setPosition(index);
            c.setPosition(index + target.length(), QTextCursor::KeepAnchor);
            pTextEdit->setTextCursor(c);
        }
    }
    else if(ui->rbUp->isChecked()){
        index = text.lastIndexOf(target, c.position() - text.length() - 1, ui->checkBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);
        if(index >= 0){
            c.setPosition(index + target.length());
            c.setPosition(index, QTextCursor::KeepAnchor);
            pTextEdit->setTextCursor(c);
        }
    }

    if(index < 0){
        QMessageBox msg(this);
        msg.setWindowTitle("记事本");
        msg.setText(QString("找不到") + target);
        msg.setWindowFlag(Qt::Drawer);
        msg.setIcon(QMessageBox::Information);
        msg.setStandardButtons(QMessageBox::Ok);
        msg.exec();
    }
}

void SearchDialog::on_btCancel_clicked()  // 修改：btnCancel → btCancel
{
    accept();
}
