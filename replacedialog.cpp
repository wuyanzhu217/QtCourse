#include "replacedialog.h"
#include "ui_replacedialog.h"
#include <QMessageBox>

ReplaceDialog::ReplaceDialog(QWidget *parent, QPlainTextEdit *textEdit)
    : QDialog(parent)
    , ui(new Ui::ReplaceDialog)
    , searchWrapped(false)  // 初始化搜索循环标志
{
    ui->setupUi(this);
    pTextEdit = textEdit;
    ui->rbDown->setChecked(true);
}

ReplaceDialog::~ReplaceDialog()
{
    delete ui;
}

void ReplaceDialog::on_btCancel_clicked()  // 查找下一个
{
    QString target = ui->searchText->text();

    if(target.isEmpty() || pTextEdit == nullptr){
        return;
    }

    QString text = pTextEdit->toPlainText();
    QTextCursor cursor = pTextEdit->textCursor();
    int index = -1;

    Qt::CaseSensitivity sensitivity = ui->checkBox->isChecked() ?
                                   Qt::CaseSensitive : Qt::CaseInsensitive;

    if(ui->rbDown->isChecked()){
        // 向下搜索
        index = text.indexOf(target, cursor.position(), sensitivity);

        if(index == -1 && cursor.position() > 0){
            // 如果没找到，从开头重新搜索
            index = text.indexOf(target, 0, sensitivity);
            if(index != -1){
                searchWrapped = true;
                QMessageBox::information(this, "提示", "已搜索到文档末尾，从开头继续搜索");
            }
        }
    } else {
        // 向上搜索
        index = text.lastIndexOf(target, cursor.position() - 1, sensitivity);

        if(index == -1 && cursor.position() < text.length()){
            // 如果没找到，从末尾重新搜索
            index = text.lastIndexOf(target, text.length(), sensitivity);
            if(index != -1){
                searchWrapped = true;
                QMessageBox::information(this, "提示", "已搜索到文档开头，从末尾继续搜索");
            }
        }
    }

    if(index >= 0){
        cursor.setPosition(index);
        cursor.setPosition(index + target.length(), QTextCursor::KeepAnchor);
        pTextEdit->setTextCursor(cursor);
        searchWrapped = false;  // 重置循环标志
    } else {
        if(searchWrapped){
            QMessageBox::information(this, "提示", "已搜索完整篇文档，未找到匹配项");
            searchWrapped = false;
        } else {
            QMessageBox::information(this, "提示", QString("找不到\"%1\"").arg(target));
        }
    }
}

void ReplaceDialog::on_btFindText_clicked()  // 替换当前并查找下一个
{
    QString target = ui->searchText->text();
    QString to = ui->ReplaceText->text();

    if((pTextEdit != nullptr) && (target != "") && (to != "")){
        QTextCursor cursor = pTextEdit->textCursor();
        QString selectedText = cursor.selectedText();

        // 如果选中的文本与目标匹配，则替换
        Qt::CaseSensitivity sensitivity = ui->checkBox->isChecked() ?
                                       Qt::CaseSensitive : Qt::CaseInsensitive;

        if(selectedText.compare(target, sensitivity) == 0){
            cursor.insertText(to);
        }

        // 查找下一个匹配项
        on_btCancel_clicked();
    } else {
        // 如果没有替换文本，直接查找下一个
        on_btCancel_clicked();
    }
}

void ReplaceDialog::on_btReplace_clicked()  // 全部替换
{
    QString target = ui->searchText->text();
    QString to = ui->ReplaceText->text();

    if((pTextEdit != nullptr) && (target != "") && (to != "")){
        QString text = pTextEdit->toPlainText();
        int count = 0;

        // 计算替换次数
        Qt::CaseSensitivity sensitivity = ui->checkBox->isChecked() ?
                                       Qt::CaseSensitive : Qt::CaseInsensitive;
        int pos = 0;
        while ((pos = text.indexOf(target, pos, sensitivity)) != -1) {
            count++;
            pos += target.length();
        }

        if(count > 0){
            // 执行替换
            text.replace(target, to, sensitivity);

            // 保存当前光标位置
            QTextCursor savedCursor = pTextEdit->textCursor();

            pTextEdit->setPlainText(text);

            // 恢复光标位置
            pTextEdit->setTextCursor(savedCursor);

            QMessageBox::information(this, "替换完成", QString("共替换了 %1 个匹配项").arg(count));
        } else {
            QMessageBox::information(this, "替换", "未找到匹配项");
        }
    } else {
        QMessageBox::warning(this, "替换", "请输入查找目标和替换内容");
    }
}

void ReplaceDialog::on_btReplaceAll_clicked()  // 取消/关闭
{
    this->close();
}
