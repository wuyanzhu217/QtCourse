/********************************************************************************
** Form generated from reading UI file 'informationwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFORMATIONWIDGET_H
#define UI_INFORMATIONWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_informationwidget
{
public:
    QGridLayout *gridLayout;
    QLabel *informationlabel;

    void setupUi(QWidget *informationwidget)
    {
        if (informationwidget->objectName().isEmpty())
            informationwidget->setObjectName("informationwidget");
        informationwidget->resize(398, 195);
        gridLayout = new QGridLayout(informationwidget);
        gridLayout->setObjectName("gridLayout");
        informationlabel = new QLabel(informationwidget);
        informationlabel->setObjectName("informationlabel");
        QFont font;
        font.setPointSize(22);
        informationlabel->setFont(font);
        informationlabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(informationlabel, 0, 0, 1, 1);


        retranslateUi(informationwidget);

        QMetaObject::connectSlotsByName(informationwidget);
    } // setupUi

    void retranslateUi(QWidget *informationwidget)
    {
        informationwidget->setWindowTitle(QCoreApplication::translate("informationwidget", "Form", nullptr));
        informationlabel->setText(QCoreApplication::translate("informationwidget", "\346\266\210\346\201\257\346\217\220\351\206\222", nullptr));
    } // retranslateUi

};

namespace Ui {
    class informationwidget: public Ui_informationwidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFORMATIONWIDGET_H
