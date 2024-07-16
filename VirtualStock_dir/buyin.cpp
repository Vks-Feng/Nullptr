#include "buyin.h"
#include "ui_buyin.h"
#include "mainwindow.h"


buyin::buyin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::buyin)
{
    ui->setupUi(this);
    qDebug() << "v1";
    this->setFixedSize(this->width(), this->height());
    initBuyInSellOut();
    qDebug() << "v2";
    IstmCharts* item_1=new IstmCharts;
    ui->verticalLayout->addWidget(item_1);
    item_1->ChangeStock(0);


    // QVBoxLayout *_layout = new QVBoxLayout(ui->selloutBroadChart);
    IstmCharts* item_2=new IstmCharts;
     ui->verticalLayout_5->addWidget(item_2);
    // _layout->addWidget(item_2);
    item_2->ChangeStock(0);

    connect(ui->BuyInStockCodeBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            item_1, &IstmCharts::ChangeStock);

    connect(ui->SellOutStockCodeBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            item_1, &IstmCharts::ChangeStock);

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
}

void buyin::on_BuyInButton_clicked()
{
    setBuyInInfo();
    ui->stackedWidget->setCurrentIndex(0);
}

void buyin::on_SellOutButton_clicked()
{
    setSellOutInfo();
    ui->stackedWidget->setCurrentIndex(1);
}

void buyin::on_TradingRecordButton_clicked()
{
    recordTableUpdate();
    ui->stackedWidget->setCurrentIndex(2);
}

void buyin::on_PositionButton_clicked()
{
    holdingTableUpdate();
    ui->stackedWidget->setCurrentIndex(3);
}

void buyin::on_IncomeButton_clicked()
{
    incomePageUpdate();
    ui->stackedWidget->setCurrentIndex(4);
}

void buyin::setBuyInName(int index){
    switch(index)
    {
    case 1:
        ui->BuyInNameLine->setText("Apple");
        break;
    case 2:
        ui->BuyInNameLine->setText("Amazon");
        break;
    case 3:
        ui->BuyInNameLine->setText("Google");
        break;
    case 4:
        ui->BuyInNameLine->setText("IBM");
        break;
    case 5:
        ui->BuyInNameLine->setText("Intel");
        break;
    case 6:
        ui->BuyInNameLine->setText("JetBlue");
        break;
    case 7:
        ui->BuyInNameLine->setText("Meta");
        break;
    case 8:
        ui->BuyInNameLine->setText("Microsoft");
        break;
    case 9:
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
    case 1:
        ui->SellOutNameLine->setText("Apple");
        break;
    case 2:
        ui->SellOutNameLine->setText("Amazon");
        break;
    case 3:
        ui->SellOutNameLine->setText("Google");
        break;
    case 4:
        ui->SellOutNameLine->setText("IBM");
        break;
    case 5:
        ui->SellOutNameLine->setText("Intel");
        break;
    case 6:
        ui->SellOutNameLine->setText("JetBlue");
        break;
    case 7:
        ui->SellOutNameLine->setText("Meta");
        break;
    case 8:
        ui->SellOutNameLine->setText("Microsoft");
        break;
    case 9:
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
    setBuyInInfo();
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
        int userID = Global::instance().getGlobalUserManage()->GetUser(0)->GetId();
        //判断用户的账户余额是否能够完成交易（钱够不够）
        if(Global::instance().getGlobalDataBase()->GetBalance(userID) >= totalPrice){
            bool highRisk = totalPrice > 0.6 * Global::instance().getGlobalDataBase()->GetBalance(userID);
            if(highRisk){
                //显示风险提示对话框
                RiskNotice warningDialog;
                if(warningDialog.exec() == QDialog::Rejected){
                    //用户取消交易
                    buyinNotification("交易取消");
                    return;
                }
            }
            //用户余额减少，更新用户
            Global::instance().getGlobalDataBase()->declineBalance(userID, totalPrice);
            //读取该笔交易的数据，构建出一条Record
            int stockID = ui->BuyInStockCodeBox->currentIndex()+1;
            QString date = QString::number(Global::instance().getYear())+"-"+QString::number(Global::instance().getGlobalDataBase()->getTime(userID));
            Record a(date,stockID,ui->BuyInQuantityLine->text().toInt(),true,(long)totalPrice);
            //用户账号添加一条记录，更新用户
            Global::instance().getGlobalDataBase()->addRecord(userID, a);
            Global::instance().getGlobalDataBase()->AddStock(userID, stockID, ui->BuyInQuantityLine->text().toInt());
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
        QString date = QString::number(Global::instance().getYear())+"-"+QString::number(Global::instance().getGlobalDataBase()->getTime(userID));
        Record r(date,stockID,ui->SellOutQuantityLine->text().toInt(),false,(long)totalPrice);
        Global::instance().getGlobalDataBase()->RemoveStock(userID, stockID, ui->SellOutQuantityLine->text().toInt());//减股票
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
    int BuyInindex = ui->BuyInStockCodeBox->currentIndex() + 1;
    setPicResource(BuyInindex);
    int userID = Global::instance().getGlobalUserManage()->GetUser(0)->GetId();
    int year = Global::instance().getYear();
    int month = Global::instance().getGlobalDataBase()->getTime(userID);
    long BuyInPrice = Global::instance().getGlobalDataBase()->getStockInfo(BuyInindex,year,month)[0];
    int balanceValue = Global::instance().getGlobalDataBase()->GetBalance(userID);
    long maxBuyInNum =  balanceValue / BuyInPrice;
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

void buyin::setSellOutInfo(){
    int SellOutindex = ui->SellOutStockCodeBox->currentIndex() + 1;
    setPicResource(SellOutindex);
    qDebug() << "SellOutindex:" << SellOutindex;
    int userID = Global::instance().getGlobalUserManage()->GetUser(0)->GetId();
    int year = Global::instance().getYear();
    int month = Global::instance().getGlobalDataBase()->getTime(userID);
    long SellOutPrice = Global::instance().getGlobalDataBase()->getStockInfo(SellOutindex,year,month)[0];
    int SellOutMaxNum = Global::instance().getGlobalDataBase()->getUserPortfolio(userID).getHoldings(SellOutindex);
    int balanceValue = Global::instance().getGlobalDataBase()->GetBalance(userID);
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
    ui->RecordTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->RecordTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    for(int i = 0; i < 5; i++){
//        ui->holdingTable->resizeColumnToContents(i);
//    }
    int userID = Global::instance().getGlobalUserManage()->GetUser(0)->GetId();
    std::vector<Record> r = Global::instance().getGlobalDataBase()->getUserRecord(userID);
    ui->RecordTable->setRowCount(r.size());
    int row = ui->RecordTable->rowCount();
//    for(int i = 0; i < row; i++){
//        ui->holdingTable->resizeRowToContents(i);
//    }
    QTableWidgetItem* iDate;
    QTableWidgetItem* iStockID;
    QTableWidgetItem* iQuantity;
    QTableWidgetItem* iTradeType;
    QTableWidgetItem* iTotalValue;
    for (int i = 0; i < row; i++) {
        iDate = new QTableWidgetItem(r[i].GetDate());
        iStockID = new QTableWidgetItem(Global::instance().getGlobalDataBase()->Id2Name(r[i].GetCompanyId()));
        iQuantity = new QTableWidgetItem(QString::number(r[i].GetVolume()));
        iTradeType = new QTableWidgetItem(r[i].GetTradeType() ? "买入" : "卖出");
        iTotalValue = new QTableWidgetItem(QString::number(r[i].GetTotalPrice()));
        ui->RecordTable->setItem(i, 0, iDate);
        ui->RecordTable->setItem(i, 1, iStockID);
        ui->RecordTable->setItem(i, 2, iQuantity);
        ui->RecordTable->setItem(i, 3, iTradeType);
        ui->RecordTable->setItem(i, 4, iTotalValue);
    }
}

void buyin::holdingTableUpdate(){
    ui->holdingTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->holdingTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    for(int i = 0; i < 3; i++){
//        ui->holdingTable->resizeColumnToContents(0);
//        ui->holdingTable->resizeColumnToContents(1);
//        ui->holdingTable->resizeColumnToContents(2);
//    }
//    for(int i = 0; i < 8; i++){
//        ui->holdingTable->resizeRowToContents(i);
//    }
    int userID = Global::instance().getGlobalUserManage()->GetUser(0)->GetId();
    Portfolio* userHoldings = &Global::instance().getGlobalDataBase()->getUserPortfolio(userID);
    QTableWidgetItem* iHolding;
    QTableWidgetItem* iTotalValue;
    long summaryHolding = 0;
    long summaryValue = 0;
    for(int i = 0; i < 8; i++){
        int year = Global::instance().getYear();
        int month = Global::instance().getGlobalDataBase()->getTime(userID);
        int holdings = userHoldings->getHoldings(i+1);
        int singleValue = Global::instance().getGlobalDataBase()->getStockInfo(i+1, year, month)[0];
        int totalValue = holdings * singleValue;
        iHolding = new QTableWidgetItem(QString::number(userHoldings->getHoldings(i+1)));
        iTotalValue = new QTableWidgetItem(QString::number(totalValue));
        ui->holdingTable->setItem(i, 0, iHolding);
        ui->holdingTable->setItem(i, 1, iTotalValue);
        summaryHolding += holdings;
        summaryValue += totalValue;
    }
    iHolding = new QTableWidgetItem(QString::number(summaryHolding));
    iTotalValue = new QTableWidgetItem(QString::number(summaryValue));
    ui->holdingTable->setItem(8, 0, iHolding);
    ui->holdingTable->setItem(8, 1, iTotalValue);
}

void buyin::setPicResource(int index){
    switch(index)
    {
    case 1:
        ui->selloutBrandIcon->setStyleSheet("background-image: url(:/new/logo/photos/Apple.png);background-position:center;background-repeat:no-repeat;");
        ui->buyinBrandIcon->setStyleSheet("background-image: url(:/new/logo/photos/Apple.png);background-position:center;background-repeat:no-repeat;");
        break;
    case 2:
        ui->selloutBrandIcon->setStyleSheet("background-image: url(:/new/logo/photos/Amazon.png);background-position:center;background-repeat:no-repeat;");
        ui->buyinBrandIcon->setStyleSheet("background-image: url(:/new/logo/photos/Amazon.png);background-position:center;background-repeat:no-repeat;");
        break;
    case 3:
        ui->selloutBrandIcon->setStyleSheet("background-image: url(:/new/logo/photos/Google.png);background-position:center;background-repeat:no-repeat;");
        ui->buyinBrandIcon->setStyleSheet("background-image: url(:/new/logo/photos/Google.png);background-position:center;background-repeat:no-repeat;");
        break;
    case 4:
        ui->selloutBrandIcon->setStyleSheet("background-image: url(:/new/logo/photos/IBM.png);background-position:center;background-repeat:no-repeat;");
        ui->buyinBrandIcon->setStyleSheet("background-image: url(:/new/logo/photos/IBM.png);background-position:center;background-repeat:no-repeat;");
        break;
    case 5:
        ui->selloutBrandIcon->setStyleSheet("background-image: url(:/new/logo/photos/Intel.png);background-position:center;background-repeat:no-repeat;");
        ui->buyinBrandIcon->setStyleSheet("background-image: url(:/new/logo/photos/Intel.png);background-position:center;background-repeat:no-repeat;");

        break;
    case 6:
        ui->selloutBrandIcon->setStyleSheet("background-image: url(:/new/logo/photos/JetBlue.png);background-position:center;background-repeat:no-repeat;");
        ui->buyinBrandIcon->setStyleSheet("background-image: url(:/new/logo/photos/JetBlue.png);background-position:center;background-repeat:no-repeat;");

        break;
    case 7:
        ui->selloutBrandIcon->setStyleSheet("background-image: url(:/new/logo/photos/Meta.png);background-position:center;background-repeat:no-repeat;");
        ui->buyinBrandIcon->setStyleSheet("background-image: url(:/new/logo/photos/Meta.png);background-position:center;background-repeat:no-repeat;");
        break;
    case 8:
        ui->selloutBrandIcon->setStyleSheet("background-image: url(:/new/logo/photos/Microsoft.png);background-position:center;background-repeat:no-repeat;");
        ui->buyinBrandIcon->setStyleSheet("background-image: url(:/new/logo/photos/Microsoft.png);background-position:center;background-repeat:no-repeat;");
        break;
    case 9:
        ui->selloutBrandIcon->setStyleSheet("background-image: url(:/new/logo/photos/Apple.png);background-position:center;background-repeat:no-repeat;");
        ui->buyinBrandIcon->setStyleSheet("background-image: url(:/new/logo/photos/Apple.png);background-position:center;background-repeat:no-repeat;");
        break;
    default:
        ui->selloutBrandIcon->setStyleSheet("background-image: url(:/new/logo/photos/Apple.png);background-position:center;background-repeat:no-repeat;");
        ui->buyinBrandIcon->setStyleSheet("background-image: url(:/new/logo/photos/Apple.png);background-position:center;background-repeat:no-repeat;");
        break;
    }
}

void buyin::incomePageUpdate(){
    ui->incometable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->incometable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    int userID = Global::instance().getGlobalUserManage()->GetUser(0)->GetId();

    // QTableWidget *tableWidget = new QTableWidget(9, 7);
    // QStringList headerLabels;
    // headerLabels << "公司股票"<< "上月股价"<<"本月股价"<< "持有量"<<"上月总股价"<<"本月总股价"<<"盈亏";
    // tableWidget->setHorizontalHeaderLabels(headerLabels);
    Portfolio* userHoldings = &Global::instance().getGlobalDataBase()->getUserPortfolio(userID);
    QTableWidgetItem* iHolding;
    QTableWidgetItem* singlevalue;
    QTableWidgetItem* lastsinglevalue;
    QTableWidgetItem* iTotalValue;
    QTableWidgetItem* iPlaceHolder;
    QTableWidgetItem* lastiTotalValue;
    QTableWidgetItem* Bep;
    QTableWidgetItem* Rate;
    long summaryHolding = 0;
    long summaryValue = 0;
    long summarylastValue=0;
    // QStringList company_names = {
    //                              "AAPL", "AMZN", "GOOGL", "IBM", "INTC",
    //                              "JBLU", "META", "MSFT", "total"};
    for(int i = 0; i < 8; i++){
        int year = Global::instance().getYear();
        int month = Global::instance().getGlobalDataBase()->getTime(userID);
        // QTableWidgetItem* iStockID= new QTableWidgetItem(QString(company_names[i]));
        int holdings = userHoldings->getHoldings(i+1);
        int singleValue = Global::instance().getGlobalDataBase()->getStockInfo(i+1, year, month)[0];
        int lastsingleValue;
        int totalValue = holdings * singleValue;
        if(month==1){
            lastsingleValue=0;
        }
        else{
            lastsingleValue = Global::instance().getGlobalDataBase()->getStockInfo(i+1, year, month-1)[0];}
        int lastvalue = holdings * lastsingleValue;
        int bep=totalValue-lastvalue;
        int rate;
        if(month==1){
            rate=0;
        }
        else{rate=100*(singleValue-lastsingleValue)/lastsingleValue;}
        singlevalue= new QTableWidgetItem(QString::number(singleValue));
        lastsinglevalue= new QTableWidgetItem(QString::number(lastsingleValue));
        iHolding = new QTableWidgetItem(QString::number(userHoldings->getHoldings(i+1)));
        iTotalValue = new QTableWidgetItem(QString::number(totalValue));
        lastiTotalValue = new QTableWidgetItem(QString::number(lastvalue));
        Bep = new QTableWidgetItem(QString::number(bep));
        Rate =new QTableWidgetItem(QString::number(rate)+"%");
        // tableWidget->setItem(i,0,iStockID);
        ui->incometable->setItem(i,0,lastsinglevalue);
        ui->incometable->setItem(i,1,singlevalue);
        ui->incometable->setItem(i, 2, iHolding);
        ui->incometable->setItem(i, 3, lastiTotalValue);
        ui->incometable->setItem(i, 4, iTotalValue);
        ui->incometable->setItem(i, 5, Bep);
        ui->incometable->setItem(i, 6, Rate);
        summaryHolding += holdings;
        summaryValue += totalValue;
        summarylastValue+=lastvalue;
    }
    // QTableWidgetItem* iStockID= new QTableWidgetItem(QString(company_names[8]));
    int totalbep= summaryValue-summarylastValue;
    double totalrate;
    if(summarylastValue==0){

        totalrate=0;
    }
    else{
        totalrate= 100*(summaryValue-summarylastValue)/summarylastValue;
    }
    iHolding = new QTableWidgetItem(QString::number(summaryHolding));
    iTotalValue = new QTableWidgetItem(QString::number(summaryValue));
    iPlaceHolder = new QTableWidgetItem("/");
    lastiTotalValue = new QTableWidgetItem(QString::number(summarylastValue));
    Bep = new QTableWidgetItem(QString::number(totalbep));
    Rate =new QTableWidgetItem(QString::number(totalrate)+"%");
    ui->incometable->setItem(8, 0, iPlaceHolder);
    ui->incometable->setItem(8, 1, iPlaceHolder);
    ui->incometable->setItem(8, 2, iHolding);
    ui->incometable->setItem(8, 4, iTotalValue);
    ui->incometable->setItem(8, 3, lastiTotalValue);
    ui->incometable->setItem(8, 5, Bep);
    ui->incometable->setItem(8, 6, Rate);
}
