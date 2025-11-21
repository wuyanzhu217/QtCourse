#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionAbout_triggered();
    void on_actionFind_triggered();
    void on_actionReplace_triggered();
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    bool on_actionSaveAs_triggered();
    void on_textEdit_textChanged();
    bool userEditConfirmed();
    void on_actionUndo_triggered();
    void on_actionCut_triggered();
    void on_actioRedo_triggered();
    void on_actionCopy_triggered();
    void on_actionPaste_triggered();
    void on_textEdit_copyAvailable(bool b);
    void on_textEdit_redoAvailable(bool b);
    void on_textEdit_undoAvailable(bool b);
    void on_actionFontColor_triggered();
    void on_actionEditor_triggered();
    void on_actionFontBackgroundColor_triggered();
    void on_actionAutomaticWrap_triggered();
    void on_actionFont_triggered();
    void on_actionToolBar_triggered();
    void on_actionStatusBar_triggered();
    void on_actionExit_triggered();
    void on_actionSelectAll_triggered();
    void on_textEdit_cursorPositionChanged();
    void on_actionDisplayLineNumber_triggered();

private:
    Ui::MainWindow *ui;
    QString FilePath;
    bool textChanged;
    QLabel statusLabel;
    QLabel statusCursorLabel;
};

#endif // MAINWINDOW_H
