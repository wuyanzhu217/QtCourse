#ifndef REPLACEDIALOG_H
#define REPLACEDIALOG_H

#include <QDialog>
#include <QPlainTextEdit>

namespace Ui {
class ReplaceDialog;
}

class ReplaceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReplaceDialog(QWidget *parent = nullptr, QPlainTextEdit *textEdit = nullptr);
    ~ReplaceDialog();

private slots:
    void on_btCancel_clicked();      // 查找下一个
    void on_btFindText_clicked();    // 替换当前并查找下一个
    void on_btReplace_clicked();     // 全部替换
    void on_btReplaceAll_clicked();  // 取消/关闭

private:
    Ui::ReplaceDialog *ui;
    QPlainTextEdit *pTextEdit;
    bool searchWrapped;  // 添加搜索循环标志
};

#endif // REPLACEDIALOG_H
