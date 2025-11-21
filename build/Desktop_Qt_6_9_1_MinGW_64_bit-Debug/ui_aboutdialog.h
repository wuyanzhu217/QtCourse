/********************************************************************************
** Form generated from reading UI file 'aboutdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTDIALOG_H
#define UI_ABOUTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AboutDialog
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_5;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout;
    QLabel *label_6;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *AboutDialog)
    {
        if (AboutDialog->objectName().isEmpty())
            AboutDialog->setObjectName("AboutDialog");
        AboutDialog->resize(628, 324);
        gridLayout = new QGridLayout(AboutDialog);
        gridLayout->setObjectName("gridLayout");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        label = new QLabel(AboutDialog);
        label->setObjectName("label");
        QFont font;
        font.setFamilies({QString::fromUtf8("Agency FB")});
        font.setPointSize(28);
        label->setFont(font);

        verticalLayout_2->addWidget(label);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_5 = new QLabel(AboutDialog);
        label_5->setObjectName("label_5");
        label_5->setStyleSheet(QString::fromUtf8("border-image: url(:/img/\347\274\226\350\276\221\345\231\250.png);"));
        label_5->setPixmap(QPixmap(QString::fromUtf8(":/img/editor2.png")));

        horizontalLayout_2->addWidget(label_5);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label_2 = new QLabel(AboutDialog);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(AboutDialog);
        label_3->setObjectName("label_3");

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(AboutDialog);
        label_4->setObjectName("label_4");

        verticalLayout->addWidget(label_4);


        horizontalLayout_2->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(5);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(5, 5, 5, 5);
        label_6 = new QLabel(AboutDialog);
        label_6->setObjectName("label_6");

        horizontalLayout->addWidget(label_6);

        buttonBox = new QDialogButtonBox(AboutDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Ok);

        horizontalLayout->addWidget(buttonBox);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 2);
        verticalLayout_2->setStretch(2, 3);

        gridLayout->addLayout(verticalLayout_2, 0, 0, 1, 1);


        retranslateUi(AboutDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, AboutDialog, qOverload<>(&QDialog::reject));
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, AboutDialog, qOverload<>(&QDialog::accept));

        QMetaObject::connectSlotsByName(AboutDialog);
    } // setupUi

    void retranslateUi(QDialog *AboutDialog)
    {
        AboutDialog->setWindowTitle(QCoreApplication::translate("AboutDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("AboutDialog", "\345\260\217\347\211\233\346\226\207\346\234\254\347\274\226\350\276\221\345\231\250", nullptr));
        label_5->setText(QString());
        label_2->setText(QCoreApplication::translate("AboutDialog", "\345\274\200\345\217\221\350\200\205\357\274\232\345\220\264\344\277\212\347\203\250", nullptr));
        label_3->setText(QCoreApplication::translate("AboutDialog", "\345\255\246\345\217\267\357\274\2322023414300217", nullptr));
        label_4->setText(QCoreApplication::translate("AboutDialog", "email\357\274\2323571276608@qq.com", nullptr));
        label_6->setText(QCoreApplication::translate("AboutDialog", "V0.1 build 20231111", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AboutDialog: public Ui_AboutDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTDIALOG_H
