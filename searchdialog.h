#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include <QPlainTextEdit>

namespace Ui {
class SearchDialog;  // 注意：类名改为 SearchDialog（大写S）
}

class SearchDialog : public QDialog  // 类名改为 SearchDialog
{
    Q_OBJECT

public:
    explicit SearchDialog(QWidget *parent = nullptr, QPlainTextEdit *textEdit = nullptr);
    ~SearchDialog();

private slots:
    void on_btFindNext_clicked();  // 修改：btnFindNext → btFindNext
    void on_btCancel_clicked();     // 修改：btnCancel → btCancel

private:
    Ui::SearchDialog *ui;  // 修改：searchDialog → SearchDialog
    QPlainTextEdit *pTextEdit;
};

#endif // SEARCHDIALOG_H
