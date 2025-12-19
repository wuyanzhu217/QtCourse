/********************************************************************************
** Form generated from reading UI file 'patientmanagerwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PATIENTMANAGERWIDGET_H
#define UI_PATIENTMANAGERWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_patientManagerwidget
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *returnbtn;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QTableView *tableView;

    void setupUi(QWidget *patientManagerwidget)
    {
        if (patientManagerwidget->objectName().isEmpty())
            patientManagerwidget->setObjectName("patientManagerwidget");
        patientManagerwidget->resize(703, 441);
        gridLayout = new QGridLayout(patientManagerwidget);
        gridLayout->setObjectName("gridLayout");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        returnbtn = new QPushButton(patientManagerwidget);
        returnbtn->setObjectName("returnbtn");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/return.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        returnbtn->setIcon(icon);

        horizontalLayout_2->addWidget(returnbtn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        horizontalLayout_3->addLayout(horizontalLayout_2);

        label = new QLabel(patientManagerwidget);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(15);
        label->setFont(font);
        label->setAlignment(Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignTop);

        horizontalLayout_3->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        lineEdit = new QLineEdit(patientManagerwidget);
        lineEdit->setObjectName("lineEdit");

        horizontalLayout->addWidget(lineEdit);

        pushButton = new QPushButton(patientManagerwidget);
        pushButton->setObjectName("pushButton");

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(patientManagerwidget);
        pushButton_2->setObjectName("pushButton_2");

        horizontalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(patientManagerwidget);
        pushButton_3->setObjectName("pushButton_3");

        horizontalLayout->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(patientManagerwidget);
        pushButton_4->setObjectName("pushButton_4");

        horizontalLayout->addWidget(pushButton_4);


        verticalLayout->addLayout(horizontalLayout);

        tableView = new QTableView(patientManagerwidget);
        tableView->setObjectName("tableView");

        verticalLayout->addWidget(tableView);


        verticalLayout_2->addLayout(verticalLayout);


        gridLayout->addLayout(verticalLayout_2, 0, 0, 1, 1);


        retranslateUi(patientManagerwidget);

        QMetaObject::connectSlotsByName(patientManagerwidget);
    } // setupUi

    void retranslateUi(QWidget *patientManagerwidget)
    {
        patientManagerwidget->setWindowTitle(QCoreApplication::translate("patientManagerwidget", "Form", nullptr));
        returnbtn->setText(QString());
        label->setText(QCoreApplication::translate("patientManagerwidget", "\346\202\243\350\200\205\347\256\241\347\220\206", nullptr));
        pushButton->setText(QCoreApplication::translate("patientManagerwidget", "\346\237\245\346\211\276", nullptr));
        pushButton_2->setText(QCoreApplication::translate("patientManagerwidget", "\346\267\273\345\212\240", nullptr));
        pushButton_3->setText(QCoreApplication::translate("patientManagerwidget", "\345\210\240\351\231\244", nullptr));
        pushButton_4->setText(QCoreApplication::translate("patientManagerwidget", "\344\277\256\346\224\271", nullptr));
    } // retranslateUi

};

namespace Ui {
    class patientManagerwidget: public Ui_patientManagerwidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PATIENTMANAGERWIDGET_H
