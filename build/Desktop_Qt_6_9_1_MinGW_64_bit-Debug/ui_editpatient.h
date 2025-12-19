/********************************************************************************
** Form generated from reading UI file 'editpatient.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITPATIENT_H
#define UI_EDITPATIENT_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_editPatient
{
public:
    QLabel *label;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *nameline;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QLineEdit *cardIdline;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QComboBox *sexcombox;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_6;
    QDateEdit *dateEdit;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_7;
    QSpinBox *heightspinBox;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_8;
    QSpinBox *weigthspinBox;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_9;
    QLineEdit *phonelineEdit;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_5;

    void setupUi(QWidget *editPatient)
    {
        if (editPatient->objectName().isEmpty())
            editPatient->setObjectName("editPatient");
        editPatient->resize(587, 405);
        label = new QLabel(editPatient);
        label->setObjectName("label");
        label->setGeometry(QRect(170, 20, 171, 21));
        QFont font;
        font.setPointSize(13);
        label->setFont(font);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        layoutWidget = new QWidget(editPatient);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(150, 70, 220, 221));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName("label_3");
        label_3->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout_2->addWidget(label_3);

        nameline = new QLineEdit(layoutWidget);
        nameline->setObjectName("nameline");
        nameline->setMinimumSize(QSize(150, 0));
        nameline->setMaximumSize(QSize(150, 16777215));

        horizontalLayout_2->addWidget(nameline);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName("label_4");
        label_4->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout_3->addWidget(label_4);

        cardIdline = new QLineEdit(layoutWidget);
        cardIdline->setObjectName("cardIdline");
        cardIdline->setMinimumSize(QSize(150, 0));
        cardIdline->setMaximumSize(QSize(150, 16777215));

        horizontalLayout_3->addWidget(cardIdline);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName("label_5");
        label_5->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout_4->addWidget(label_5);

        sexcombox = new QComboBox(layoutWidget);
        sexcombox->addItem(QString());
        sexcombox->addItem(QString());
        sexcombox->setObjectName("sexcombox");
        sexcombox->setMinimumSize(QSize(150, 0));
        sexcombox->setMaximumSize(QSize(150, 16777215));

        horizontalLayout_4->addWidget(sexcombox);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName("label_6");
        label_6->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout_5->addWidget(label_6);

        dateEdit = new QDateEdit(layoutWidget);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setMinimumSize(QSize(150, 0));
        dateEdit->setMaximumSize(QSize(150, 16777215));

        horizontalLayout_5->addWidget(dateEdit);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName("label_7");
        label_7->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout_6->addWidget(label_7);

        heightspinBox = new QSpinBox(layoutWidget);
        heightspinBox->setObjectName("heightspinBox");
        heightspinBox->setMinimumSize(QSize(150, 0));
        heightspinBox->setMaximumSize(QSize(150, 16777215));
        heightspinBox->setMaximum(200);

        horizontalLayout_6->addWidget(heightspinBox);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName("label_8");
        label_8->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout_7->addWidget(label_8);

        weigthspinBox = new QSpinBox(layoutWidget);
        weigthspinBox->setObjectName("weigthspinBox");
        weigthspinBox->setMinimumSize(QSize(150, 0));
        weigthspinBox->setMaximumSize(QSize(150, 16777215));
        weigthspinBox->setMaximum(200);

        horizontalLayout_7->addWidget(weigthspinBox);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        label_9 = new QLabel(layoutWidget);
        label_9->setObjectName("label_9");
        label_9->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout_8->addWidget(label_9);

        phonelineEdit = new QLineEdit(layoutWidget);
        phonelineEdit->setObjectName("phonelineEdit");
        phonelineEdit->setMinimumSize(QSize(150, 0));
        phonelineEdit->setMaximumSize(QSize(150, 16777215));

        horizontalLayout_8->addWidget(phonelineEdit);


        verticalLayout->addLayout(horizontalLayout_8);

        layoutWidget1 = new QWidget(editPatient);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(380, 230, 77, 56));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(layoutWidget1);
        pushButton->setObjectName("pushButton");

        verticalLayout_2->addWidget(pushButton);

        pushButton_2 = new QPushButton(layoutWidget1);
        pushButton_2->setObjectName("pushButton_2");

        verticalLayout_2->addWidget(pushButton_2);

        pushButton_5 = new QPushButton(editPatient);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(10, 20, 28, 24));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/return.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_5->setIcon(icon);

        retranslateUi(editPatient);

        QMetaObject::connectSlotsByName(editPatient);
    } // setupUi

    void retranslateUi(QWidget *editPatient)
    {
        editPatient->setWindowTitle(QCoreApplication::translate("editPatient", "Form", nullptr));
        label->setText(QCoreApplication::translate("editPatient", "\347\274\226\350\276\221\346\202\243\350\200\205\344\277\241\346\201\257", nullptr));
        label_3->setText(QCoreApplication::translate("editPatient", "\345\247\223\345\220\215:", nullptr));
        label_4->setText(QCoreApplication::translate("editPatient", "\350\272\253\344\273\275\350\257\201:", nullptr));
        label_5->setText(QCoreApplication::translate("editPatient", "\346\200\247\345\210\253:", nullptr));
        sexcombox->setItemText(0, QCoreApplication::translate("editPatient", "\347\224\267", nullptr));
        sexcombox->setItemText(1, QCoreApplication::translate("editPatient", "\345\245\263", nullptr));

        label_6->setText(QCoreApplication::translate("editPatient", "\345\207\272\347\224\237\346\227\245\346\234\237:", nullptr));
        label_7->setText(QCoreApplication::translate("editPatient", "\350\272\253\351\253\230:", nullptr));
        label_8->setText(QCoreApplication::translate("editPatient", "\344\275\223\351\207\215:", nullptr));
        label_9->setText(QCoreApplication::translate("editPatient", "\346\211\213\346\234\272\345\217\267:", nullptr));
        pushButton->setText(QCoreApplication::translate("editPatient", "\344\277\235\345\255\230", nullptr));
        pushButton_2->setText(QCoreApplication::translate("editPatient", "\345\217\226\346\266\210", nullptr));
        pushButton_5->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class editPatient: public Ui_editPatient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITPATIENT_H
