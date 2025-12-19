/********************************************************************************
** Form generated from reading UI file 'loginwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWIDGET_H
#define UI_LOGINWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_loginwidget
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *roombtn;
    QPushButton *doctorbtn;
    QPushButton *patientbtn;
    QLabel *label;
    QPushButton *returnbtn;

    void setupUi(QWidget *loginwidget)
    {
        if (loginwidget->objectName().isEmpty())
            loginwidget->setObjectName("loginwidget");
        loginwidget->resize(562, 365);
        layoutWidget = new QWidget(loginwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(90, 120, 360, 110));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(25);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(5, 5, 5, 5);
        roombtn = new QPushButton(layoutWidget);
        roombtn->setObjectName("roombtn");
        roombtn->setMinimumSize(QSize(100, 100));

        horizontalLayout->addWidget(roombtn);

        doctorbtn = new QPushButton(layoutWidget);
        doctorbtn->setObjectName("doctorbtn");
        doctorbtn->setMinimumSize(QSize(100, 100));

        horizontalLayout->addWidget(doctorbtn);

        patientbtn = new QPushButton(layoutWidget);
        patientbtn->setObjectName("patientbtn");
        patientbtn->setMinimumSize(QSize(100, 100));

        horizontalLayout->addWidget(patientbtn);

        label = new QLabel(loginwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(210, 10, 91, 31));
        QFont font;
        font.setPointSize(14);
        label->setFont(font);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        returnbtn = new QPushButton(loginwidget);
        returnbtn->setObjectName("returnbtn");
        returnbtn->setGeometry(QRect(20, 10, 28, 24));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/return.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        returnbtn->setIcon(icon);

        retranslateUi(loginwidget);

        QMetaObject::connectSlotsByName(loginwidget);
    } // setupUi

    void retranslateUi(QWidget *loginwidget)
    {
        loginwidget->setWindowTitle(QCoreApplication::translate("loginwidget", "Form", nullptr));
        roombtn->setText(QCoreApplication::translate("loginwidget", "\347\247\221\345\256\244\347\256\241\347\220\206", nullptr));
        doctorbtn->setText(QCoreApplication::translate("loginwidget", "\345\214\273\347\224\237\347\256\241\347\220\206", nullptr));
        patientbtn->setText(QCoreApplication::translate("loginwidget", "\346\202\243\350\200\205\347\256\241\347\220\206", nullptr));
        label->setText(QCoreApplication::translate("loginwidget", "\346\254\242\350\277\216", nullptr));
        returnbtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class loginwidget: public Ui_loginwidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWIDGET_H
