#include "buyin.h"
#include "ui_buyin.h"
#include "mainwindow.h"
buyin::buyin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::buyin)
{
    ui->setupUi(this);
    initBuyInSellOut();
}

buyin::~buyin()
{
    delete ui;
}

void buyin::initBuyInSellOut(){
    ui->BuyInStockCodeBox->setCurrentIndex(0);
    ui->SellOutStockCodeBox->setCurrentIndex(0);
    ui->stackedWidget->setCurrentIndex(0);
    Global::instance().getGlobalUserManage()->updateUser(0);
    setBuyInInfo();
    //setSellOutInfo();
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

void buyin::setBuyInName(int index){
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
}

void buyin::setSellOutName(int index){
    switch(index)
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

void buyin::on_BuyInStockCodeBox_currentIndexChanged(int index){
    setBuyInInfo();
}

void buyin::on_SellOutStockCodeBox_currentIndexChanged(int index){
    setSellOutInfo();
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
    else if(ui->BuyInQuantityLine->text().toInt() > ui->BuyInMaxLine->text().toInt()){
        buyinNotification("买入数量超限，购买失败");
        return;
    }
    else{
        //读取ui中输入的买入数量，已经对应股票的单价，计算该笔交易的金额
        int totalPrice = ui->BuyInPriceLine->text().toInt() * ui->BuyInQuantityLine->text().toInt();
        //获取用户id
        int id = Global::instance().getGlobalUserManage()->GetUser(0)->GetId();
        //判断用户的账户余额是否能够完成交易（钱够不够）
        if(Global::instance().getGlobalDataBase()->GetBalance(id) > totalPrice){
            //用户余额减少，更新用户
            Global::instance().getGlobalDataBase()->declineBalance(id, totalPrice);
            Global::instance().getGlobalUserManage()->updateUser(0);
            //读取该笔交易的数据，构建出一条Record
            int stockID = ui->BuyInStockCodeBox->currentIndex()+1;
            QString date = QString::number(Global::instance().getYear())+"-"+QString::number(Global::instance().getMonth());
            Record a(date,stockID,ui->BuyInQuantityLine->text().toInt(),true,(long)totalPrice);
            //用户账号添加一条记录，更新用户
            Global::instance().getGlobalDataBase()->addRecord(id, a);
            Global::instance().getGlobalUserManage()->updateUser(0);
            //提示购买成功并重置页面状态
            buyinNotification("购买成功");
            initBuyInSellOut();
        } else {
            buyinNotification("金额不足，购买失败");
        }
    }
}

void buyin::on_SellResetButton_clicked()
{
    ui->SellOutStockCodeBox->setCurrentIndex(0);
    initBuyInSellOut();
}


void buyin::on_SellComfirmButton_clicked()
{   if(ui->SellOutButton->text().isEmpty()){
        buyinNotification("请填写卖出数量");
        return;
    }
    else if(ui->SellOutQuantityLine->text().toInt() > ui->SellOutMaxLine->text().toInt()){
        buyinNotification("持股不足，卖出失败");
        return;
    }
    else{
        Global::instance().getGlobalUserManage()->updateUser(0);
        int userID = Global::instance().getGlobalUserManage()->GetUser(0)->GetId();
        int stockID = ui->SellOutStockCodeBox->currentIndex() + 1;
        int totalPrice = ui->SellOutPriceLine->text().toInt() * ui->SellOutQuantityLine->text().toInt();
        int year = Global::instance().getYear();
        int month = Global::instance().getMonth();
        QString date=QString::number(year)+" "+QString::number(month);
        Record r(date,stockID,ui->SellOutQuantityLine->text().toInt(),false,(long)totalPrice);
        Global::instance().getGlobalUserManage()->GetUser(0)->GetPortfolio()->removeStock(stockID,ui->SellOutQuantityLine->text().toInt());//减股票
        Global::instance().getGlobalDataBase()->inclineBalance(userID, totalPrice);//加钱
        Global::instance().getGlobalDataBase()->addRecord(userID,r);
        initBuyInSellOut();
    }
}

void buyin::buyinNotification(QString msg){
    QMessageBox msgBox;
    msgBox.setText(msg);
    msgBox.exec();
}

void buyin::setBuyInInfo(){
    int BuyInindex = ui->BuyInStockCodeBox->currentIndex();
    int year = Global::instance().getYear();
    int month = Global::instance().getMonth();
    int BuyInPrice = Global::instance().getGlobalDataBase()->getStockInfo(BuyInindex+1,year,month)[0];
    int maxBuyInNum = Global::instance().getGlobalDataBase()->getStockInfo(BuyInindex+1,year,month)[1];
    int balanceValue = Global::instance().getGlobalUserManage()->GetUser(0)->GetVir().GetValue();
    setBuyInName(BuyInindex);
    ui->BuyInNameLine->setDisabled(true);
    ui->BuyInPriceLine->setText(QString::number(BuyInPrice));
    ui->BuyInPriceLine->setDisabled(true);
    ui->BuyInFundLine->setText(QString::number(balanceValue));
    ui->BuyInFundLine->setDisabled(true);
    ui->BuyInMaxLine->setText(QString::number(maxBuyInNum));
    ui->BuyInMaxLine->setDisabled(true);
    ui->BuyInQuantityLine->setText("");
    ui->BuyInQuantityLine->setValidator(new QIntValidator(0, maxBuyInNum, ui->BuyInQuantityLine));
}

//void buyin::setSellOutInfo(){
//    int SellOutindex = ui->SellOutStockCodeBox->currentIndex();
//    int year = Global::instance().getYear();
//    int month = Global::instance().getMonth();
//    int userID = Global::instance().getGlobalUserManage()->GetUser(0)->GetId();
//    Global::instance().getGlobalUserManage()->updateUser(userID);
//    int SellOutPrice = Global::instance().getGlobalDataBase()->getStockInfo(SellOutindex+1,year,month)[0];
//    int SellOutMaxNum = Global::instance().getGlobalDataBase()->getUserPortfolio(userID).getHoldings(SellOutindex);
//    int balanceValue = Global::instance().getGlobalUserManage()->GetUser(0)->GetVir().GetValue();
//    setSellOutName(SellOutindex);
//    ui->SellOutNameLine->setDisabled(true);
//    ui->SellOutPriceLine->setText(QString::number(SellOutPrice));
//    ui->SellOutPriceLine->setDisabled(true);
//    ui->SellOutFundLine->setText(QString::number(balanceValue));
//    ui->SellOutFundLine->setDisabled(true);
//    ui->SellOutMaxLine->setText(QString::number(SellOutMaxNum));
//    ui->SellOutMaxLine->setDisabled(true);
//    ui->SellOutQuantityLine->setText("");
//    ui->SellOutQuantityLine->setValidator(new QIntValidator(0, SellOutMaxNum, ui->SellOutQuantityLine));
//}

void buyin::setSellOutInfo(){
    int SellOutindex = ui->SellOutStockCodeBox->currentIndex();
    qDebug() << "SellOutindex:" << SellOutindex;

    int year = Global::instance().getYear();
    int month = Global::instance().getMonth();

    auto user = Global::instance().getGlobalUserManage()->GetUser(0);
    if (!user) {
        qDebug() << "User is nullptr";
        return;
    } else {
        qDebug() << "User is valid";
    }
    int userID = user->GetId();
    Global::instance().getGlobalUserManage()->updateUser(userID);

    auto stockInfo = Global::instance().getGlobalDataBase()->getStockInfo(SellOutindex + 1, year, month);
    if (stockInfo.empty()) {
        qDebug() << "Stock info is empty";
        return;
    } else {
        qDebug() << "Stock info is valid";
    }
    int SellOutPrice = stockInfo[0];

    auto portfolio = Global::instance().getGlobalDataBase()->getUserPortfolio(userID);
    int SellOutMaxNum = portfolio.getHoldings(SellOutindex);

    int balanceValue = user->GetVir().GetValue();

    if (!ui->SellOutNameLine || !ui->SellOutPriceLine || !ui->SellOutFundLine || !ui->SellOutMaxLine || !ui->SellOutQuantityLine) {
        qDebug() << "One of the UI elements is nullptr";
        return;
    } else {
        qDebug() << "ui is valid";
    }

    setSellOutName(SellOutindex);
    ui->SellOutNameLine->setDisabled(true);
    ui->SellOutPriceLine->setText(QString::number(SellOutPrice));
    ui->SellOutPriceLine->setDisabled(true);
    ui->SellOutFundLine->setText(QString::number(balanceValue));
    ui->SellOutFundLine->setDisabled(true);
    ui->SellOutMaxLine->setText(QString::number(SellOutMaxNum));
    ui->SellOutMaxLine->setDisabled(true);
    ui->SellOutQuantityLine->setText("");
    ui->SellOutQuantityLine->setValidator(new QIntValidator(0, SellOutMaxNum, ui->SellOutQuantityLine));
}


void buyin::recordTableUpdate(){
    Global::instance().getGlobalUserManage()->updateUser(0);
    std::vector<Record> r = Global::instance().getGlobalUserManage()->GetUser(0)->GetRecord();
    ui->RecordTable->setRowCount(r.size());
    int row = ui->RecordTable->rowCount();
    QTableWidgetItem* iDate;
    QTableWidgetItem* iStockID;
    QTableWidgetItem* iQuantity;
    QTableWidgetItem* iTradeType;
    QTableWidgetItem* iTotalValue;
    for (int i = 0; i < row; i++) {
        iDate = new QTableWidgetItem(r[i].GetDate());
        iStockID = new QTableWidgetItem(r[i].GetCompanyId());
        iQuantity = new QTableWidgetItem(r[i].GetVolume());
        iTradeType = new QTableWidgetItem(r[i].GetTradeType() ? "买入" : "卖出");
        iTotalValue = new QTableWidgetItem(r[i].GetTotalPrice());
        ui->RecordTable->setItem(i, 0, iDate);
        ui->RecordTable->setItem(i, 1, iStockID);
        ui->RecordTable->setItem(i, 2, iQuantity);
        ui->RecordTable->setItem(i, 3, iTradeType);
        ui->RecordTable->setItem(i, 4, iTotalValue);
    }
}

void buyin::holdingTableUpdate(){
    Global::instance().getGlobalUserManage()->updateUser(0);
    Portfolio* userHoldings = Global::instance().getGlobalUserManage()->GetUser(0)->GetPortfolio();
    QTableWidgetItem* iHolding;
    QTableWidgetItem* iTotalValue;
    for(int i = 0; i < 9; i++){
        int year = Global::instance().getYear();
        int month = Global::instance().getMonth();
        int holdings = userHoldings->getHoldings(i);
        int singleValue = Global::instance().getGlobalDataBase()->getStockInfo(i+1, year, month)[0];
        int totalValue = holdings * singleValue;
        iHolding = new QTableWidgetItem(userHoldings->getHoldings(i));
        iTotalValue = new QTableWidgetItem(totalValue);
        ui->holdingTable->setItem(i, 0, iHolding);
        ui->holdingTable->setItem(i, 1, iTotalValue);
    }
}
