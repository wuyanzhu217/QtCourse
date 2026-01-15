/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *Filelabel;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_target_device;
    QComboBox *combo_target_device;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *btn_select_files;
    QPushButton *btn_clear_queue;
    QTableView *tableView_transfer;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btn_start_transfer;
    QPushButton *btn_pause_transfer;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btn_cancel_transfer;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(605, 471);
        gridLayout = new QGridLayout(Widget);
        gridLayout->setObjectName("gridLayout");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        Filelabel = new QLabel(Widget);
        Filelabel->setObjectName("Filelabel");
        QFont font;
        font.setPointSize(20);
        Filelabel->setFont(font);

        horizontalLayout_5->addWidget(Filelabel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_target_device = new QLabel(Widget);
        label_target_device->setObjectName("label_target_device");

        horizontalLayout->addWidget(label_target_device);

        combo_target_device = new QComboBox(Widget);
        combo_target_device->setObjectName("combo_target_device");

        horizontalLayout->addWidget(combo_target_device);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        btn_select_files = new QPushButton(Widget);
        btn_select_files->setObjectName("btn_select_files");

        horizontalLayout_4->addWidget(btn_select_files);

        btn_clear_queue = new QPushButton(Widget);
        btn_clear_queue->setObjectName("btn_clear_queue");

        horizontalLayout_4->addWidget(btn_clear_queue);


        verticalLayout_2->addLayout(horizontalLayout_4);

        tableView_transfer = new QTableView(Widget);
        tableView_transfer->setObjectName("tableView_transfer");

        verticalLayout_2->addWidget(tableView_transfer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        btn_start_transfer = new QPushButton(Widget);
        btn_start_transfer->setObjectName("btn_start_transfer");

        horizontalLayout_2->addWidget(btn_start_transfer);

        btn_pause_transfer = new QPushButton(Widget);
        btn_pause_transfer->setObjectName("btn_pause_transfer");

        horizontalLayout_2->addWidget(btn_pause_transfer);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        btn_cancel_transfer = new QPushButton(Widget);
        btn_cancel_transfer->setObjectName("btn_cancel_transfer");

        horizontalLayout_3->addWidget(btn_cancel_transfer);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_3);


        verticalLayout_2->addLayout(verticalLayout);


        gridLayout->addLayout(verticalLayout_2, 0, 0, 1, 1);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        Filelabel->setText(QCoreApplication::translate("Widget", "\345\261\200\345\237\237\347\275\221\346\226\207\344\273\266\344\274\240\350\276\223\347\263\273\347\273\237", nullptr));
        label_target_device->setText(QCoreApplication::translate("Widget", "\347\233\256\346\240\207\350\256\276\345\244\207\357\274\232", nullptr));
        btn_select_files->setText(QCoreApplication::translate("Widget", "\351\200\211\346\213\251\346\226\207\344\273\266", nullptr));
        btn_clear_queue->setText(QCoreApplication::translate("Widget", "\346\270\205\347\251\272\351\230\237\345\210\227", nullptr));
        btn_start_transfer->setText(QCoreApplication::translate("Widget", "\345\274\200\345\247\213\344\274\240\350\276\223", nullptr));
        btn_pause_transfer->setText(QCoreApplication::translate("Widget", "\346\232\202\345\201\234\344\274\240\350\276\223", nullptr));
        btn_cancel_transfer->setText(QCoreApplication::translate("Widget", "\345\217\226\346\266\210\344\274\240\350\276\223", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
