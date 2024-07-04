/********************************************************************************
** Form generated from reading UI file 'buyin.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUYIN_H
#define UI_BUYIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_buyin
{
public:
    QStackedWidget *stackedWidget;
    QWidget *BuyinPage;
    QWidget *SellOutPage;
    QWidget *RecordPage;
    QWidget *PositionPage;
    QWidget *IncomePage;
    QWidget *RecommendPage;
    QLabel *label;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QPushButton *BuyInButton;
    QPushButton *SellOutButton;
    QPushButton *TradingRecordButton;
    QPushButton *PositionButton;
    QPushButton *IncomeButton;
    QPushButton *RecommendButton;

    void setupUi(QWidget *buyin)
    {
        if (buyin->objectName().isEmpty())
            buyin->setObjectName("buyin");
        buyin->resize(600, 465);
        stackedWidget = new QStackedWidget(buyin);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(130, 50, 461, 391));
        BuyinPage = new QWidget();
        BuyinPage->setObjectName("BuyinPage");
        stackedWidget->addWidget(BuyinPage);
        SellOutPage = new QWidget();
        SellOutPage->setObjectName("SellOutPage");
        stackedWidget->addWidget(SellOutPage);
        RecordPage = new QWidget();
        RecordPage->setObjectName("RecordPage");
        stackedWidget->addWidget(RecordPage);
        PositionPage = new QWidget();
        PositionPage->setObjectName("PositionPage");
        stackedWidget->addWidget(PositionPage);
        IncomePage = new QWidget();
        IncomePage->setObjectName("IncomePage");
        stackedWidget->addWidget(IncomePage);
        RecommendPage = new QWidget();
        RecommendPage->setObjectName("RecommendPage");
        label = new QLabel(RecommendPage);
        label->setObjectName("label");
        label->setGeometry(QRect(260, 130, 63, 18));
        stackedWidget->addWidget(RecommendPage);
        widget = new QWidget(buyin);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(10, 20, 94, 431));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        BuyInButton = new QPushButton(widget);
        BuyInButton->setObjectName("BuyInButton");

        verticalLayout->addWidget(BuyInButton);

        SellOutButton = new QPushButton(widget);
        SellOutButton->setObjectName("SellOutButton");

        verticalLayout->addWidget(SellOutButton);

        TradingRecordButton = new QPushButton(widget);
        TradingRecordButton->setObjectName("TradingRecordButton");

        verticalLayout->addWidget(TradingRecordButton);

        PositionButton = new QPushButton(widget);
        PositionButton->setObjectName("PositionButton");

        verticalLayout->addWidget(PositionButton);

        IncomeButton = new QPushButton(widget);
        IncomeButton->setObjectName("IncomeButton");

        verticalLayout->addWidget(IncomeButton);

        RecommendButton = new QPushButton(widget);
        RecommendButton->setObjectName("RecommendButton");

        verticalLayout->addWidget(RecommendButton);


        retranslateUi(buyin);

        stackedWidget->setCurrentIndex(5);


        QMetaObject::connectSlotsByName(buyin);
    } // setupUi

    void retranslateUi(QWidget *buyin)
    {
        buyin->setWindowTitle(QCoreApplication::translate("buyin", "Form", nullptr));
        label->setText(QCoreApplication::translate("buyin", "1", nullptr));
        BuyInButton->setText(QCoreApplication::translate("buyin", "\344\271\260\345\205\245", nullptr));
        SellOutButton->setText(QCoreApplication::translate("buyin", "\345\215\226\345\207\272", nullptr));
        TradingRecordButton->setText(QCoreApplication::translate("buyin", "\344\272\244\346\230\223\350\256\260\345\275\225", nullptr));
        PositionButton->setText(QCoreApplication::translate("buyin", "\346\214\201\344\273\223\350\202\241\347\245\250", nullptr));
        IncomeButton->setText(QCoreApplication::translate("buyin", "\346\224\266\347\233\212", nullptr));
        RecommendButton->setText(QCoreApplication::translate("buyin", "\344\274\230\350\264\250\350\202\241\347\245\250\346\216\250\350\215\220", nullptr));
    } // retranslateUi

};

namespace Ui {
    class buyin: public Ui_buyin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUYIN_H
