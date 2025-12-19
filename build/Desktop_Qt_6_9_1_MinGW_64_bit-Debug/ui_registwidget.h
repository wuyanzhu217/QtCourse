/********************************************************************************
** Form generated from reading UI file 'registwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTWIDGET_H
#define UI_REGISTWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_registwidget
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *NamelineEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *UseNamelineEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *passwordlineEdit;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QPushButton *cancelbtn;
    QPushButton *registbtn;
    QPushButton *returnbtn;
    QLabel *label_4;

    void setupUi(QWidget *registwidget)
    {
        if (registwidget->objectName().isEmpty())
            registwidget->setObjectName("registwidget");
        registwidget->resize(591, 355);
        layoutWidget = new QWidget(registwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(60, 100, 181, 121));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(layoutWidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        NamelineEdit = new QLineEdit(layoutWidget);
        NamelineEdit->setObjectName("NamelineEdit");

        horizontalLayout->addWidget(NamelineEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        UseNamelineEdit = new QLineEdit(layoutWidget);
        UseNamelineEdit->setObjectName("UseNamelineEdit");

        horizontalLayout_2->addWidget(UseNamelineEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName("label_3");

        horizontalLayout_3->addWidget(label_3);

        passwordlineEdit = new QLineEdit(layoutWidget);
        passwordlineEdit->setObjectName("passwordlineEdit");

        horizontalLayout_3->addWidget(passwordlineEdit);


        verticalLayout->addLayout(horizontalLayout_3);

        layoutWidget1 = new QWidget(registwidget);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(250, 160, 77, 56));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        cancelbtn = new QPushButton(layoutWidget1);
        cancelbtn->setObjectName("cancelbtn");

        verticalLayout_2->addWidget(cancelbtn);

        registbtn = new QPushButton(layoutWidget1);
        registbtn->setObjectName("registbtn");

        verticalLayout_2->addWidget(registbtn);

        returnbtn = new QPushButton(registwidget);
        returnbtn->setObjectName("returnbtn");
        returnbtn->setGeometry(QRect(0, 10, 28, 24));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/return.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        returnbtn->setIcon(icon);
        label_4 = new QLabel(registwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(150, 10, 61, 31));
        QFont font;
        font.setPointSize(16);
        label_4->setFont(font);
        label_4->setAlignment(Qt::AlignmentFlag::AlignCenter);

        retranslateUi(registwidget);

        QMetaObject::connectSlotsByName(registwidget);
    } // setupUi

    void retranslateUi(QWidget *registwidget)
    {
        registwidget->setWindowTitle(QCoreApplication::translate("registwidget", "Form", nullptr));
        label->setText(QCoreApplication::translate("registwidget", "\345\247\223\345\220\215\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("registwidget", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("registwidget", "\345\257\206\347\240\201\357\274\232", nullptr));
        cancelbtn->setText(QCoreApplication::translate("registwidget", "\345\217\226\346\266\210", nullptr));
        registbtn->setText(QCoreApplication::translate("registwidget", "\346\263\250\345\206\214", nullptr));
        returnbtn->setText(QString());
        label_4->setText(QCoreApplication::translate("registwidget", "\346\263\250\345\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class registwidget: public Ui_registwidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTWIDGET_H
