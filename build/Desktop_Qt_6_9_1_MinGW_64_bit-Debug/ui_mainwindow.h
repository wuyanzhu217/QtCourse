/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <codeeditor.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSaveAs;
    QAction *actionExit;
    QAction *actionUndo;
    QAction *actioRedo;
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionFind;
    QAction *actionReplace;
    QAction *actionSelectAll;
    QAction *actionAutomaticWrap;
    QAction *actionDisplayLineNumber;
    QAction *actionFont;
    QAction *actionFontColor;
    QAction *actionFontBackgroundColor;
    QAction *actionEditor;
    QAction *actionToolBar;
    QAction *actionStatusBar;
    QAction *actionAbout;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    CodeEditor *textEdit;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_O;
    QMenu *menu_V;
    QMenu *menu_3;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(625, 390);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/editor.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        MainWindow->setWindowIcon(icon);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName("actionNew");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/img/new.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionNew->setIcon(icon1);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName("actionOpen");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/img/file.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionOpen->setIcon(icon2);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName("actionSave");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/img/savefile.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionSave->setIcon(icon3);
        actionSaveAs = new QAction(MainWindow);
        actionSaveAs->setObjectName("actionSaveAs");
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/img/save2.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionSaveAs->setIcon(icon4);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName("actionExit");
        QIcon icon5(QIcon::fromTheme(QIcon::ThemeIcon::ApplicationExit));
        actionExit->setIcon(icon5);
        actionUndo = new QAction(MainWindow);
        actionUndo->setObjectName("actionUndo");
        QIcon icon6;
        if (QIcon::hasThemeIcon(QIcon::ThemeIcon::EditUndo)) {
            icon6 = QIcon::fromTheme(QIcon::ThemeIcon::EditUndo);
        } else {
            icon6.addFile(QString::fromUtf8(":/img/\344\270\212\344\270\200\346\255\245_back.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        }
        actionUndo->setIcon(icon6);
        actioRedo = new QAction(MainWindow);
        actioRedo->setObjectName("actioRedo");
        QIcon icon7;
        if (QIcon::hasThemeIcon(QIcon::ThemeIcon::EditRedo)) {
            icon7 = QIcon::fromTheme(QIcon::ThemeIcon::EditRedo);
        } else {
            icon7.addFile(QString::fromUtf8(":/img/\344\270\213\344\270\200\346\255\245_next.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        }
        actioRedo->setIcon(icon7);
        actionCut = new QAction(MainWindow);
        actionCut->setObjectName("actionCut");
        QIcon icon8;
        if (QIcon::hasThemeIcon(QIcon::ThemeIcon::EditCut)) {
            icon8 = QIcon::fromTheme(QIcon::ThemeIcon::EditCut);
        } else {
            icon8.addFile(QString::fromUtf8(":/img/\350\243\201\345\210\207_cutting-one.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        }
        actionCut->setIcon(icon8);
        actionCopy = new QAction(MainWindow);
        actionCopy->setObjectName("actionCopy");
        QIcon icon9;
        if (QIcon::hasThemeIcon(QIcon::ThemeIcon::EditCopy)) {
            icon9 = QIcon::fromTheme(QIcon::ThemeIcon::EditCopy);
        } else {
            icon9.addFile(QString::fromUtf8(":/img/\345\244\215\345\210\266_copy.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        }
        actionCopy->setIcon(icon9);
        actionPaste = new QAction(MainWindow);
        actionPaste->setObjectName("actionPaste");
        QIcon icon10;
        if (QIcon::hasThemeIcon(QIcon::ThemeIcon::EditPaste)) {
            icon10 = QIcon::fromTheme(QIcon::ThemeIcon::EditPaste);
        } else {
            icon10.addFile(QString::fromUtf8(":/img/\347\262\230\350\264\264.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        }
        actionPaste->setIcon(icon10);
        actionFind = new QAction(MainWindow);
        actionFind->setObjectName("actionFind");
        QIcon icon11;
        if (QIcon::hasThemeIcon(QIcon::ThemeIcon::EditFind)) {
            icon11 = QIcon::fromTheme(QIcon::ThemeIcon::EditFind);
        } else {
            icon11.addFile(QString::fromUtf8(":/img/\346\237\245\346\211\276.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        }
        actionFind->setIcon(icon11);
        actionReplace = new QAction(MainWindow);
        actionReplace->setObjectName("actionReplace");
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/img/file-conversion-one.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionReplace->setIcon(icon12);
        actionSelectAll = new QAction(MainWindow);
        actionSelectAll->setObjectName("actionSelectAll");
        QIcon icon13;
        if (QIcon::hasThemeIcon(QIcon::ThemeIcon::EditSelectAll)) {
            icon13 = QIcon::fromTheme(QIcon::ThemeIcon::EditSelectAll);
        } else {
            icon13.addFile(QString::fromUtf8(":/img/autoswitchline.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        }
        actionSelectAll->setIcon(icon13);
        actionAutomaticWrap = new QAction(MainWindow);
        actionAutomaticWrap->setObjectName("actionAutomaticWrap");
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/img/autoswitchline.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionAutomaticWrap->setIcon(icon14);
        actionDisplayLineNumber = new QAction(MainWindow);
        actionDisplayLineNumber->setObjectName("actionDisplayLineNumber");
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/img/showlinenum.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionDisplayLineNumber->setIcon(icon15);
        actionFont = new QAction(MainWindow);
        actionFont->setObjectName("actionFont");
        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/img/font.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionFont->setIcon(icon16);
        actionFontColor = new QAction(MainWindow);
        actionFontColor->setObjectName("actionFontColor");
        actionFontBackgroundColor = new QAction(MainWindow);
        actionFontBackgroundColor->setObjectName("actionFontBackgroundColor");
        actionEditor = new QAction(MainWindow);
        actionEditor->setObjectName("actionEditor");
        actionToolBar = new QAction(MainWindow);
        actionToolBar->setObjectName("actionToolBar");
        QIcon icon17;
        icon17.addFile(QString::fromUtf8(":/img/tool.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionToolBar->setIcon(icon17);
        actionStatusBar = new QAction(MainWindow);
        actionStatusBar->setObjectName("actionStatusBar");
        QIcon icon18;
        icon18.addFile(QString::fromUtf8(":/img/statebar.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionStatusBar->setIcon(icon18);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName("actionAbout");
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(1, 1, 1, 1);
        textEdit = new CodeEditor(centralWidget);
        textEdit->setObjectName("textEdit");

        verticalLayout->addWidget(textEdit);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 625, 22));
        menu = new QMenu(menuBar);
        menu->setObjectName("menu");
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName("menu_2");
        menu_O = new QMenu(menuBar);
        menu_O->setObjectName("menu_O");
        menu_V = new QMenu(menuBar);
        menu_V->setObjectName("menu_V");
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName("menu_3");
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName("mainToolBar");
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu_O->menuAction());
        menuBar->addAction(menu_V->menuAction());
        menuBar->addAction(menu_3->menuAction());
        menu->addAction(actionNew);
        menu->addAction(actionOpen);
        menu->addAction(actionSave);
        menu->addAction(actionSaveAs);
        menu->addSeparator();
        menu->addAction(actionExit);
        menu_2->addAction(actionUndo);
        menu_2->addAction(actioRedo);
        menu_2->addAction(actionCut);
        menu_2->addAction(actionCopy);
        menu_2->addAction(actionPaste);
        menu_2->addSeparator();
        menu_2->addAction(actionFind);
        menu_2->addAction(actionReplace);
        menu_2->addSeparator();
        menu_2->addAction(actionSelectAll);
        menu_O->addAction(actionAutomaticWrap);
        menu_O->addAction(actionDisplayLineNumber);
        menu_O->addAction(actionFont);
        menu_O->addAction(actionFontColor);
        menu_O->addSeparator();
        menu_O->addAction(actionFontBackgroundColor);
        menu_O->addAction(actionEditor);
        menu_V->addAction(actionToolBar);
        menu_V->addAction(actionStatusBar);
        menu_3->addAction(actionAbout);
        toolBar->addAction(actionNew);
        toolBar->addAction(actionOpen);
        toolBar->addAction(actionSave);
        toolBar->addAction(actionSaveAs);
        toolBar->addSeparator();
        toolBar->addAction(actionUndo);
        toolBar->addAction(actioRedo);
        toolBar->addAction(actionCut);
        toolBar->addAction(actionCopy);
        toolBar->addAction(actionPaste);
        toolBar->addSeparator();
        toolBar->addAction(actionFind);
        toolBar->addAction(actionReplace);
        toolBar->addSeparator();
        toolBar->addAction(actionAutomaticWrap);
        toolBar->addAction(actionDisplayLineNumber);
        toolBar->addAction(actionFont);
        toolBar->addSeparator();
        toolBar->addAction(actionToolBar);
        toolBar->addAction(actionStatusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionNew->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\273\272\357\274\210&F\357\274\211", nullptr));
#if QT_CONFIG(shortcut)
        actionNew->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        actionOpen->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\357\274\210&O\357\274\211", nullptr));
#if QT_CONFIG(shortcut)
        actionOpen->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230(&S)", nullptr));
#if QT_CONFIG(shortcut)
        actionSave->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSaveAs->setText(QCoreApplication::translate("MainWindow", "\345\217\246\345\255\230\344\270\272", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272(&X)", nullptr));
        actionUndo->setText(QCoreApplication::translate("MainWindow", "\346\222\244\351\224\200\357\274\210&U\357\274\211", nullptr));
#if QT_CONFIG(shortcut)
        actionUndo->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Z", nullptr));
#endif // QT_CONFIG(shortcut)
        actioRedo->setText(QCoreApplication::translate("MainWindow", "\345\233\236\345\244\215\357\274\210&\357\274\211", nullptr));
#if QT_CONFIG(shortcut)
        actioRedo->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+Z", nullptr));
#endif // QT_CONFIG(shortcut)
        actionCut->setText(QCoreApplication::translate("MainWindow", "\345\211\252\345\210\207\357\274\210&T\357\274\211", nullptr));
#if QT_CONFIG(shortcut)
        actionCut->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+X", nullptr));
#endif // QT_CONFIG(shortcut)
        actionCopy->setText(QCoreApplication::translate("MainWindow", "\345\244\215\345\210\266\357\274\210&C\357\274\211", nullptr));
#if QT_CONFIG(shortcut)
        actionCopy->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+C", nullptr));
#endif // QT_CONFIG(shortcut)
        actionPaste->setText(QCoreApplication::translate("MainWindow", "\347\262\230\350\264\264\357\274\210&P\357\274\211", nullptr));
#if QT_CONFIG(shortcut)
        actionPaste->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+V", nullptr));
#endif // QT_CONFIG(shortcut)
        actionFind->setText(QCoreApplication::translate("MainWindow", "\346\237\245\346\211\276\357\274\210&F\357\274\211", nullptr));
#if QT_CONFIG(shortcut)
        actionFind->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+F", nullptr));
#endif // QT_CONFIG(shortcut)
        actionReplace->setText(QCoreApplication::translate("MainWindow", "\346\233\277\346\215\242\357\274\210&R\357\274\211", nullptr));
#if QT_CONFIG(shortcut)
        actionReplace->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+H", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSelectAll->setText(QCoreApplication::translate("MainWindow", "\345\205\250\351\200\211\357\274\210&A\357\274\211", nullptr));
#if QT_CONFIG(shortcut)
        actionSelectAll->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+A", nullptr));
#endif // QT_CONFIG(shortcut)
        actionAutomaticWrap->setText(QCoreApplication::translate("MainWindow", "\350\207\252\345\212\250\346\215\242\350\241\214\357\274\210&W\357\274\211", nullptr));
        actionDisplayLineNumber->setText(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\350\241\214\345\217\267", nullptr));
        actionFont->setText(QCoreApplication::translate("MainWindow", "\345\255\227\344\275\223\357\274\210&F\357\274\211", nullptr));
        actionFontColor->setText(QCoreApplication::translate("MainWindow", "\345\255\227\344\275\223\351\242\234\350\211\262", nullptr));
        actionFontBackgroundColor->setText(QCoreApplication::translate("MainWindow", "\345\255\227\344\275\223\350\203\214\346\231\257\350\211\262", nullptr));
        actionEditor->setText(QCoreApplication::translate("MainWindow", "\347\274\226\350\276\221\345\231\250\350\203\214\346\231\257\350\211\262", nullptr));
        actionToolBar->setText(QCoreApplication::translate("MainWindow", "\345\267\245\345\205\267\346\240\217\357\274\210&T\357\274\211", nullptr));
        actionStatusBar->setText(QCoreApplication::translate("MainWindow", "\347\212\266\346\200\201\346\240\217\357\274\210&S\357\274\211", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "\345\205\263\344\272\216\357\274\210&A)", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266(&F)", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", "\347\274\226\350\276\221\357\274\210&E\357\274\211", nullptr));
        menu_O->setTitle(QCoreApplication::translate("MainWindow", "\346\240\274\345\274\217\357\274\210&O\357\274\211", nullptr));
        menu_V->setTitle(QCoreApplication::translate("MainWindow", "\346\237\245\346\211\276\357\274\210&V\357\274\211", nullptr));
        menu_3->setTitle(QCoreApplication::translate("MainWindow", "\345\270\256\345\212\251\357\274\210&H\357\274\211", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
