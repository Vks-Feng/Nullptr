/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QStackedWidget *selectpage;
    QWidget *selectpage1;
    QWidget *selectpage2;
    QGroupBox *groupBox_6;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QWidget *selectpage3;
    QWidget *selectpage4;
    QWidget *selectpage5;
    QPushButton *personpage1;
    QPushButton *leavebutton1;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QPushButton *firstbutton1;
    QPushButton *stockbutton1;
    QPushButton *rankbutton1;
    QPushButton *dealbutton1;
    QPushButton *communitybutton1;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(564, 347);
        selectpage = new QStackedWidget(MainWindow);
        selectpage->setObjectName("selectpage");
        selectpage->setGeometry(QRect(10, 80, 531, 301));
        selectpage1 = new QWidget();
        selectpage1->setObjectName("selectpage1");
        selectpage->addWidget(selectpage1);
        selectpage2 = new QWidget();
        selectpage2->setObjectName("selectpage2");
        groupBox_6 = new QGroupBox(selectpage2);
        groupBox_6->setObjectName("groupBox_6");
        groupBox_6->setGeometry(QRect(30, 30, 441, 41));
        pushButton = new QPushButton(groupBox_6);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(10, 10, 61, 24));
        pushButton_2 = new QPushButton(groupBox_6);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(100, 10, 61, 24));
        pushButton_3 = new QPushButton(groupBox_6);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(190, 10, 61, 24));
        pushButton_4 = new QPushButton(groupBox_6);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(280, 10, 61, 24));
        pushButton_5 = new QPushButton(groupBox_6);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(370, 10, 61, 24));
        pushButton_6 = new QPushButton(groupBox_6);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(460, 10, 61, 24));
        selectpage->addWidget(selectpage2);
        selectpage3 = new QWidget();
        selectpage3->setObjectName("selectpage3");
        selectpage->addWidget(selectpage3);
        selectpage4 = new QWidget();
        selectpage4->setObjectName("selectpage4");
        selectpage->addWidget(selectpage4);
        selectpage5 = new QWidget();
        selectpage5->setObjectName("selectpage5");
        selectpage->addWidget(selectpage5);
        personpage1 = new QPushButton(MainWindow);
        personpage1->setObjectName("personpage1");
        personpage1->setGeometry(QRect(470, 20, 80, 24));
        leavebutton1 = new QPushButton(MainWindow);
        leavebutton1->setObjectName("leavebutton1");
        leavebutton1->setGeometry(QRect(470, 50, 81, 24));
        groupBox = new QGroupBox(MainWindow);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 20, 448, 51));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName("horizontalLayout");
        firstbutton1 = new QPushButton(groupBox);
        firstbutton1->setObjectName("firstbutton1");
        firstbutton1->setFlat(true);

        horizontalLayout->addWidget(firstbutton1);

        stockbutton1 = new QPushButton(groupBox);
        stockbutton1->setObjectName("stockbutton1");

        horizontalLayout->addWidget(stockbutton1);

        rankbutton1 = new QPushButton(groupBox);
        rankbutton1->setObjectName("rankbutton1");

        horizontalLayout->addWidget(rankbutton1);

        dealbutton1 = new QPushButton(groupBox);
        dealbutton1->setObjectName("dealbutton1");

        horizontalLayout->addWidget(dealbutton1);

        communitybutton1 = new QPushButton(groupBox);
        communitybutton1->setObjectName("communitybutton1");
        communitybutton1->setEnabled(true);

        horizontalLayout->addWidget(communitybutton1);


        retranslateUi(MainWindow);

        selectpage->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Form", nullptr));
        groupBox_6->setTitle(QString());
        pushButton->setText(QCoreApplication::translate("MainWindow", "\344\271\260\345\205\245", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\345\215\226\345\207\272", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "\344\272\244\346\230\223\350\256\260\345\275\225", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "\346\214\201\344\273\223\350\202\241\347\245\250", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "\346\224\266\347\233\212", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "\344\274\230\350\202\241\346\216\250\350\215\220", nullptr));
        personpage1->setText(QCoreApplication::translate("MainWindow", "\344\270\252\344\272\272\344\270\273\351\241\265", nullptr));
        leavebutton1->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272\347\231\273\351\231\206", nullptr));
        groupBox->setTitle(QString());
        firstbutton1->setText(QCoreApplication::translate("MainWindow", "\351\246\226\351\241\265", nullptr));
        stockbutton1->setText(QCoreApplication::translate("MainWindow", "\350\202\241\347\245\250", nullptr));
        rankbutton1->setText(QCoreApplication::translate("MainWindow", "\346\216\222\350\241\214\346\246\234", nullptr));
        dealbutton1->setText(QCoreApplication::translate("MainWindow", "\344\272\244\346\230\223\350\247\204\345\210\231", nullptr));
        communitybutton1->setText(QCoreApplication::translate("MainWindow", "\347\244\276\345\214\272\344\272\244\346\265\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
