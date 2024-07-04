#include "buyin.h"
#include "ui_buyin.h"
#include "mainwindow.h"
buyin::buyin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::buyin)
{
    ui->setupUi(this);
}

buyin::~buyin()
{
    delete ui;
}

void buyin::on_BuyInButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void buyin::on_SellOutButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void buyin::on_TradingRecordButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void buyin::on_PositionButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void buyin::on_IncomeButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}


void buyin::on_RecommendButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}


void buyin::on_returnbutton_clicked()
{
    MainWindow* mainwindow = new MainWindow();
    mainwindow->show();
    this->close();
}

