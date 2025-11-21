#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include "searchdialog.h"
#include "replacedialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QColorDialog>
#include <QFontDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    textChanged = false;
    on_actionNew_triggered();
    statusLabel.setMaximumWidth(180);
    statusLabel.setText("length: " + QString::number(0) + " lines: " + QString::number(1));
    ui->statusBar->addPermanentWidget(&statusLabel);

    statusCursorLabel.setMaximumWidth(180);
    statusCursorLabel.setText("Ln: " + QString::number(0) + " Col: " + QString::number(1));
    ui->statusBar->addPermanentWidget(&statusCursorLabel);

    QLabel *author = new QLabel(ui->statusBar);
    author->setText(tr("吴俊烨"));
    ui->statusBar->addPermanentWidget(author);

    ui->actionCopy->setEnabled(false);
    ui->actionCut->setEnabled(false);
    //如果此处将actionPaste默认状态设置为false，该文本编辑器将不可在最开始粘贴来自外部复制的文本，因此此处设置为true
    ui->actionPaste->setEnabled(true);
    ui->actionUndo->setEnabled(false);
    ui->actioRedo->setEnabled(false);

    QPlainTextEdit::LineWrapMode mode = ui->textEdit->lineWrapMode();

    if(mode == QPlainTextEdit::NoWrap){
        ui->textEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);
        ui->actionAutomaticWrap->setChecked(true);
    }
    else{
        ui->textEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
        ui->actionAutomaticWrap->setChecked(false);
    }

    ui->actionStatusBar->setChecked(true);
    ui->actionToolBar->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog dlg;
    dlg.exec();
}

void MainWindow::on_actionFind_triggered()
{
    SearchDialog dlg(this, ui->textEdit);
    dlg.exec();
}

void MainWindow::on_actionReplace_triggered()
{
    ReplaceDialog dlg(this, ui->textEdit);
    dlg.exec();
}

void MainWindow::on_actionNew_triggered()
{
    if(!userEditConfirmed())return;
    FilePath = "";
    ui->textEdit->clear();
    this->setWindowTitle(tr("新建文本文件 - 编辑器"));
    textChanged = false;
}

void MainWindow::on_actionOpen_triggered()
{
    if(!userEditConfirmed())return;
    ui->textEdit->clear();
    QString filename = QFileDialog::getOpenFileName(this,"打开文件",".",tr("Text Files (*.txt) ;; All (*.*)"));
    QFile file(filename);

    if(!file.open(QFile::ReadOnly | QFile::Text)){
        ui->statusBar->showMessage("打开文件失败！" , 2000);
        return;
    }

    FilePath = filename;

    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->insertPlainText(text);
    file.close();

    this->setWindowTitle(QFileInfo(filename).absoluteFilePath());
    textChanged = false;
}

void MainWindow::on_actionSave_triggered()
{
    if(FilePath == ""){
        QString filename = QFileDialog::getSaveFileName(this,"保存文件",".",tr("Text Files (*.txt)"));

        QFile file(filename);
        if(!file.open(QFile::WriteOnly | QFile::Text))
        {
            ui->statusBar->showMessage("文件保存失败！" , 2000);
            return;
        }
        file.close();
        FilePath = filename;
    }

    QFile file(FilePath);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        ui->statusBar->showMessage("文件保存失败！" , 2000);
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out<<text;
    file.flush();
    file.close();
    ui->statusBar->showMessage("文件保存成功！" , 2000);
    this->setWindowTitle(QFileInfo(FilePath).absoluteFilePath());
    textChanged = false;
}

bool MainWindow::on_actionSaveAs_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this,"保存文件",".",tr("Text Files (*.txt)"));

    QFile file(filename);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        ui->statusBar->showMessage("文件保存失败！" , 2000);
        return false;
    }
    FilePath = filename;
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out<<text;
    file.flush();
    file.close();

    this->setWindowTitle(QFileInfo(FilePath).absoluteFilePath());
    ui->statusBar->showMessage("文件保存成功！" , 2000);
    return true;
}

void MainWindow::on_textEdit_textChanged()
{
    if(!textChanged){
        this->setWindowTitle("*" + this->windowTitle());
        textChanged = true;
    }

    statusLabel.setText("length: " + QString::number(ui->textEdit->toPlainText().length()) + " lines: " + QString::number(ui->textEdit->document()->lineCount()));
}

bool MainWindow::userEditConfirmed()
{
    if(textChanged){
        QString path = FilePath;
        if(path!=""){
            QMessageBox msg(this);
            msg.setIcon(QMessageBox::Question);
            msg.setWindowTitle("...");
            msg.setWindowFlag(Qt::Drawer);
            msg.setText(QString("是否将更改保存到") + "\"" + path + "\" ?");
            msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
            int r = msg.exec();
            switch(r){
            case QMessageBox::Yes:
                on_actionSave_triggered();
                break;
            case QMessageBox::No:
                textChanged = false;
                break;
            case QMessageBox::Cancel:
                return false;
            }
        }
        else{
            QMessageBox msg(this);
            msg.setIcon(QMessageBox::Question);
            msg.setWindowTitle("...");
            msg.setWindowFlag(Qt::Drawer);
            msg.setText(QString("是否将更改另存为"));
            msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
            int r = msg.exec();
            switch(r){
            case QMessageBox::Yes:
                if(!on_actionSaveAs_triggered())return false;
                break;
            case QMessageBox::No:
                textChanged = false;
                break;
            case QMessageBox::Cancel:
                return false;
            }
        }
    }
    return true;
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actioRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_textEdit_copyAvailable(bool b)
{
    ui->actionCopy->setEnabled(b);
    ui->actionCut->setEnabled(b);
}

void MainWindow::on_textEdit_redoAvailable(bool b)
{
    ui->actioRedo->setEnabled(b);
}

void MainWindow::on_textEdit_undoAvailable(bool b)
{
    ui->actionUndo->setEnabled(b);
}

void MainWindow::on_actionFontColor_triggered()
{
    QColor color = QColorDialog::getColor(Qt::black, this, "选择颜色");
    if(color.isValid()){
        ui->textEdit->setStyleSheet(QString("QPlainTextEdit{color: %1}").arg(color.name()));
    }
}

void MainWindow::on_actionEditor_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "选择背景颜色");
    if(color.isValid()){
        ui->textEdit->setStyleSheet(QString("QPlainTextEdit{background-color: %1}").arg(color.name()));
    }
}

void MainWindow::on_actionFontBackgroundColor_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "选择字体背景色");
    if(color.isValid()){
        QTextCharFormat format;
        format.setBackground(color);
        QTextCursor cursor = ui->textEdit->textCursor();
        cursor.mergeCharFormat(format);
    }
}

void MainWindow::on_actionAutomaticWrap_triggered()
{
    QPlainTextEdit::LineWrapMode mode = ui->textEdit->lineWrapMode();

    if(mode == QPlainTextEdit::NoWrap){
        ui->textEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);
        ui->actionAutomaticWrap->setChecked(true);
    }
    else{
        ui->textEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
        ui->actionAutomaticWrap->setChecked(false);
    }
}

void MainWindow::on_actionFont_triggered()
{
    bool ok = false;
    QFont font = QFontDialog::getFont(&ok,this);
    if(ok){
        ui->textEdit->setFont(font);
    }
}

void MainWindow::on_actionToolBar_triggered()
{
    bool visible = ui->toolBar->isVisible();
    ui->toolBar->setVisible(!visible);
    ui->actionToolBar->setChecked(!visible);
}

void MainWindow::on_actionStatusBar_triggered()
{
    bool visible = ui->statusBar->isVisible();
    ui->statusBar->setVisible(!visible);
    ui->actionStatusBar->setChecked(!visible);
}

void MainWindow::on_actionExit_triggered()
{
    if(userEditConfirmed())
        exit(0);
}

void MainWindow::on_actionSelectAll_triggered()
{
    ui->textEdit->selectAll();
}

void MainWindow::on_textEdit_cursorPositionChanged()
{
    int col = 0;
    int ln = 0;
    int flg = -1;
    int pos = ui->textEdit->textCursor().position();
    QString text = ui->textEdit->toPlainText();

    for(int i =0; i < pos; i++){
        if( text[i] == '\n'){
            ln ++;
            flg = i;
        }
    }

    flg++;
    col = pos - flg;
    statusCursorLabel.setText("Ln: " + QString::number(ln + 1) + " Col: " + QString::number(col + 1));
}

void MainWindow::on_actionDisplayLineNumber_triggered()
{
    // 这里可以添加显示行号功能的实现
    // 临时显示消息
    if(ui->actionDisplayLineNumber->isChecked()) {
        ui->statusBar->showMessage("行号显示功能已启用", 2000);
    } else {
        ui->statusBar->showMessage("行号显示功能已禁用", 2000);
    }
}
