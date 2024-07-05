#include "buyin.h"
#include "ui_buyin.h"
#include "mainwindow.h"
buyin::buyin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::buyin)
{
    ui->setupUi(this);
    r1=false;
    r2=false;
    ui->StockCodeBox->setCurrentIndex(0);
    resetvalue();
}

buyin::~buyin()
{
    delete ui;
}

void buyin::resetvalue(){
    int value=user->GetVir().GetValue();
    ui->FundLine->setText(QString::number(value));
}

void buyin::resetvalue_2(){
    int value=user->GetVir().GetValue();
    ui->FundLine_2->setText(QString::number(value));
}

void buyin::on_BuyInButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    r1=false;
    r2=false;
    ui->StockCodeBox->setCurrentIndex(0);
    resetvalue();
}


void buyin::on_SellOutButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    r1=false;
    r2=false;
    ui->StockCodeBox_2->setCurrentIndex(0);
    resetvalue_2();
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

void buyin::on_StockCodeBox_currentIndexChanged(int index)
{
    id=index;
    QString m="AAA";//需要一个函数，输入股票id返还这个id对应的股票中文名称
    if(id==0)
    {   ui->NameLine->setText("");
        ui->MaxBuyinLine->setText("");
        ui->PriceLine->setText("");//三栏清空，可用资金保留
        resetvalue();
        return;
    }//名字匹配

    //Stock*stock;对应id的股票
    value=stock->GetSinglePrice();
    int numa=stock->GetVolumn();
    double Rvalue=user->GetVir().GetValue();
    int numb=Rvalue/value;
    if(numa>numb){maxnum=numb;}
    else {maxnum=numa;}//计算出最大购买量
    ui->NameLine->setText(m);
    ui->MaxBuyinLine->setText(QString::number(maxnum));
    ui->PriceLine->setText(QString::number(value));
    r1=true;//第一栏填完了
}


void buyin::on_QuantityLine_textChanged(const QString &arg1)
{
    buynum=arg1.toInt();
    r2=true;//第二栏填完了
}

void buyin::on_BuyResetButton_clicked()
{
    ui->StockCodeBox->setCurrentIndex(0);
    r1=false;
    r2=false;
}

void buyin::on_BuyComfirmButton_clicked()
{   if(!r1&&!r2){
        //这里应该弹出一个提示未填写完全的窗口
        return;
    }
    else if(buynum>maxnum){
        //这里应该弹出一个可用金额不足的提示窗口，我先不在ui里面更改怕出问题
        return;
    }
    else{
        user->GetPortfolio().addStock(*stock,buynum);//加股票
        user->GetVir().withdraw(value*buynum);//扣钱
        QString data=QString::number(stock->GetYear())+" "+QString::number(stock->GetMonth());
        //记录中存储的日期格式待定，购买量int就够了不需要long,暂定true为买入,购买量你俩一个设置的double一个long，需要统一
        Record a(data,*stock,buynum,true,value*buynum);
        user->AddRecord(a);
        r1=false;
        r2=false;
        ui->StockCodeBox->setCurrentIndex(0);
        resetvalue();
    }
}

void buyin::on_StockCodeBox_2_currentIndexChanged(int index)
{
    id=index;
    QString m="AAA";//需要一个函数，输入股票id返还这个id对应的股票中文名称
    if(id==0)
    {   ui->NameLine_2->setText("");
        ui->MaxBuyinLine_2->setText("");
        ui->PriceLine_2->setText("");//三栏清空，可用资金保留
        resetvalue_2();
        return;
    }//名字匹配

    //Stock*stock;对应id的股票
    value=stock->GetSinglePrice();
    std::map hold=user->GetPortfolio().getHoldings();
    maxnum=hold[id];
    //计算出最大卖出量
    ui->NameLine_2->setText(m);
    ui->MaxBuyinLine_2->setText(QString::number(maxnum));
    ui->PriceLine_2->setText(QString::number(value));
    r1=true;//第一栏填完了
}

void buyin::on_QuantityLine_2_textChanged(const QString &arg1)
{
    buynum=arg1.toInt();
    r2=true;//第二栏填完了
}


void buyin::on_SellResetButton_clicked()
{
    ui->StockCodeBox_2->setCurrentIndex(0);
    r1=false;
    r2=false;
}


void buyin::on_SellComfirmButton_clicked()
{   if(!r1&&!r2){
        //这里应该弹出一个提示未填写完全的窗口
        return;
    }
    else if(buynum>maxnum){
        //这里应该弹出一个可用股票不足的提示窗口，我先不在ui里面更改怕出问题
        return;
    }
    else{
        user->GetPortfolio().removeStock(*stock,buynum);//减股票
        user->GetVir().deposit(value*buynum);//加钱
        QString data=QString::number(stock->GetYear())+" "+QString::number(stock->GetMonth());
        //记录中存储的日期格式待定，卖出量int就够了不需要long,暂定false为卖出,你俩一个设置的double一个long，需要统一
        Record a(data,*stock,buynum,true,value*buynum);
        user->AddRecord(a);
        r1=false;
        r2=false;
        ui->StockCodeBox_2->setCurrentIndex(0);
        resetvalue_2();
    }

}

