#include "buyin.h"
#include "ui_buyin.h"
#include "mainwindow.h"
buyin::buyin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::buyin)
{
    ui->setupUi(this);
    ui->BuyInStockCodeBox->setCurrentIndex(0);
    ui->SellOutStockCodeBox->setCurrentIndex(0);
    ui->stackedWidget->setCurrentIndex(0);
    initBuyInSellOut();
}

buyin::~buyin()
{
    delete ui;
}

void buyin::initBuyInSellOut(){
    int balanceValue=Global::instance().getGlobalUserManage()->GetUser(0)->GetVir().GetValue();
    int buyInPrice = 100;//这里之后通过数据库查询数据库中股票的价格
    int buyInMax = 99999;//这里之后通过数据库查询数据库中股票的余量
    int sellOutPrice = 100;//这里之后通过数据库查询数据库中股票的价格
    int sellOutNum = 999;//这里之后通过数据库查询数据库中用户持股数量

    ui->BuyInPriceLine->setText(QString::number(buyInPrice));
    ui->BuyInPriceLine->setDisabled(true);
    ui->BuyInFundLine->setText(QString::number(balanceValue));
    ui->BuyInFundLine->setDisabled(true);
    ui->BuyInMaxLine->setText(QString::number(buyInMax));
    ui->BuyInMaxLine->setDisabled(true);
    ui->BuyInQuantityLine->setText("");
    ui->BuyInNameLine->setDisabled(true);
    int BuyInindex = ui->BuyInStockCodeBox->currentIndex();
    switch(BuyInindex)
    {
    case 0:
        ui->BuyInNameLine->setText("Apple");
        break;
    case 1:
        ui->BuyInNameLine->setText("Amazon");
        break;
    case 2:
        ui->BuyInNameLine->setText("Google");
        break;
    case 3:
        ui->BuyInNameLine->setText("IBM");
        break;
    case 4:
        ui->BuyInNameLine->setText("Intel");
        break;
    case 5:
        ui->BuyInNameLine->setText("JetBlue");
        break;
    case 6:
        ui->BuyInNameLine->setText("Meta");
        break;
    case 7:
        ui->BuyInNameLine->setText("Microsoft");
        break;
    case 8:
        ui->BuyInNameLine->setText("Tesla");
        break;
    default:
        ui->BuyInNameLine->setText("Error");
        break;
    }

    ui->SellOutFundLine->setText(QString::number(balanceValue));
    ui->SellOutFundLine->setDisabled(true);
    ui->SellOutMaxLine->setDisabled(true);
    ui->SellOutMaxLine->setText(QString::number(sellOutNum));
    ui->SellOutQuantityLine->setText("");
    ui->SellOutPriceLine->setText(QString::number(sellOutPrice));
    ui->SellOutPriceLine->setDisabled(true);
    ui->SellOutNameLine->setDisabled(true);
    int SellOutindex = ui->SellOutStockCodeBox->currentIndex();
    switch(SellOutindex)
    {
    case 0:
        ui->SellOutNameLine->setText("Apple");
        break;
    case 1:
        ui->SellOutNameLine->setText("Amazon");
        break;
    case 2:
        ui->SellOutNameLine->setText("Google");
        break;
    case 3:
        ui->SellOutNameLine->setText("IBM");
        break;
    case 4:
        ui->SellOutNameLine->setText("Intel");
        break;
    case 5:
        ui->SellOutNameLine->setText("JetBlue");
        break;
    case 6:
        ui->SellOutNameLine->setText("Meta");
        break;
    case 7:
        ui->SellOutNameLine->setText("Microsoft");
        break;
    case 8:
        ui->SellOutNameLine->setText("Tesla");
        break;
    default:
        ui->SellOutNameLine->setText("Error");
        break;
    }
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

void buyin::on_returnbutton_clicked(){
//    暂且这么设计，有问题找vks
//    MainWindow* mainwindow = new MainWindow();
//    mainwindow->show();
    this->close();
}

void buyin::on_BuyInStockCodeBox_currentIndexChanged(int index){
    switch(index)
    {
    case 0:
        ui->BuyInNameLine->setText("Apple");
        break;
    case 1:
        ui->BuyInNameLine->setText("Amazon");
        break;
    case 2:
        ui->BuyInNameLine->setText("Google");
        break;
    case 3:
        ui->BuyInNameLine->setText("IBM");
        break;
    case 4:
        ui->BuyInNameLine->setText("Intel");
        break;
    case 5:
        ui->BuyInNameLine->setText("JetBlue");
        break;
    case 6:
        ui->BuyInNameLine->setText("Meta");
        break;
    case 7:
        ui->BuyInNameLine->setText("Microsoft");
        break;
    case 8:
        ui->BuyInNameLine->setText("Tesla");
        break;
    default:
        ui->BuyInNameLine->setText("Error");
        break;
    }
    int maxBuyInNum = 999;//这里怎么设计不知道
    ui->BuyInMaxLine->setText(QString::number(maxBuyInNum));
}

void buyin::on_SellOutStockCodeBox_currentIndexChanged(int index){
    switch(index)
    {
    case 0:
        ui->BuyInNameLine->setText("Apple");
        break;
    case 1:
        ui->BuyInNameLine->setText("Amazon");
        break;
    case 2:
        ui->BuyInNameLine->setText("Google");
        break;
    case 3:
        ui->BuyInNameLine->setText("IBM");
        break;
    case 4:
        ui->BuyInNameLine->setText("Intel");
        break;
    case 5:
        ui->BuyInNameLine->setText("JetBlue");
        break;
    case 6:
        ui->BuyInNameLine->setText("Meta");
        break;
    case 7:
        ui->BuyInNameLine->setText("Microsoft");
        break;
    case 8:
        ui->BuyInNameLine->setText("Tesla");
        break;
    default:
        ui->BuyInNameLine->setText("Error");
        break;
    }
    std::map hold=Global::instance().getGlobalUserManage()->GetUser(0)->GetPortfolio().getHoldings();
    ui->SellOutMaxLine->setText(QString::number(hold[index]));
    int sellPrice = 999;//这里之后用index到数据库或许数据
    ui->SellOutPriceLine->setText(QString::number(sellPrice));
}

void buyin::on_BuyResetButton_clicked()
{
    ui->SellOutStockCodeBox->setCurrentIndex(0);
    initBuyInSellOut();
}

void buyin::on_BuyComfirmButton_clicked()
{   if(ui->BuyInQuantityLine->text().isEmpty()){
        buyinNotification("请填写买入数量");
        return;
    }
    else if(ui->BuyInQuantityLine->text().toInt()>ui->BuyInMaxLine->text().toInt()){
        buyinNotification("资金不足，购买失败");
        return;
    }
    else{
        Global::instance().getGlobalUserManage()->GetUser(0)->GetPortfolio().addStock(ui->BuyInStockCodeBox->currentIndex(),ui->BuyInQuantityLine->text().toInt());//加股票
        int totalPrice = ui->BuyInPriceLine->text().toInt() * ui->BuyInQuantityLine->text().toInt();
        Global::instance().getGlobalUserManage()->GetUser(0)->GetVir().withdraw(totalPrice);//扣钱
        int companyId  = ui->BuyInStockCodeBox->currentIndex()+1;
        QString date = QString::number(1949)+"-"+QString::number(10);
        Record a(date,companyId,ui->BuyInQuantityLine->text().toInt(),true,(long)totalPrice);
        Global::instance().getGlobalUserManage()->GetUser(0)->AddRecord(a);
        ui->BuyInStockCodeBox->setCurrentIndex(0);
        initBuyInSellOut();
    }
}

void buyin::on_SellResetButton_clicked()
{
    ui->SellOutStockCodeBox->setCurrentIndex(0);
    initBuyInSellOut();
}


void buyin::on_SellComfirmButton_clicked()
{   if(ui->SellOutButton){
        buyinNotification("请填写卖出数量");
        return;
    }
    else if(ui->SellOutQuantityLine->text().toInt() > ui->SellOutMaxLine->text().toInt()){
        buyinNotification("持股不足，请修改");
        return;
    }
    else{
        Global::instance().getGlobalUserManage()->GetUser(0)->GetPortfolio().removeStock(ui->SellOutStockCodeBox->currentIndex(),ui->SellOutQuantityLine->text().toInt());//减股票
        int totalPrice = ui->SellOutPriceLine->text().toInt() * ui->SellOutQuantityLine->text().toInt();
        Global::instance().getGlobalUserManage()->GetUser(0)->GetVir().deposit(totalPrice);//加钱
        QString data=QString::number(1949)+" "+QString::number(10);
        int companyId  = ui->BuyInStockCodeBox->currentIndex()+1;
        Record a(data,companyId,ui->SellOutQuantityLine->text().toInt(),false,(long)totalPrice);
        Global::instance().getGlobalUserManage()->GetUser(0)->AddRecord(a);
        ui->SellOutStockCodeBox->setCurrentIndex(0);
        initBuyInSellOut();
    }

}

void buyin::buyinNotification(QString msg){
    QMessageBox msgBox;
    msgBox.setText(msg);
    msgBox.exec();
}
