#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chartspline.h"
#include <QPlainTextEdit>

struct UserData {
    QString userName;
    double totalAssets;
    int month;
    UserData(const QString& userName, double totalAssets , int month )
        : userName(userName), totalAssets(totalAssets), month(month) {}
};

bool compareByAssets(const UserData &a, const UserData &b) {
    return a.totalAssets > b.totalAssets; // 降序排序
}
MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);//无边框
    ui->logo->setScaledContents(true);//logo自适应大小



    ui->selectpage4->setLayout(ui->RuleLayout);//规则介绍布局问题
    ui->selectpage->setCurrentIndex(0);
    //将页面切换逻辑使用按钮的click进行手动转换

    ui->TransactionRule->setReadOnly(1);

    //尝试将股票的信息挂载到股票界面的layout中
    // 找到占位部件
    ChartSpline *_chartSpline_1=new ChartSpline;
    ChartSpline *_chartSpline_2=new ChartSpline;

    _chartSpline_1->ChangeStock(0);
//    connect(ui->ChangeStockShowBtn, &QPushButton::clicked, _chartSpline, &ChartSpline::ShowRandomStock);
    // 在股票界面设置显示哪一只股票
    connect(ui->ChooseWhichStock, QOverload<int>::of(&QComboBox::currentIndexChanged),
            _chartSpline_1, &ChartSpline::ChangeStock);

    QWidget *placeholder = ui->chartSplineWidget;

    ui->selectpage3->setLayout(ui->RankingLayout);
    //

    //固定大小
    this->setFixedSize(this->width(),this->height());
    // 设置 chartspline 对象到占位部件的位置
    QVBoxLayout *layout = new QVBoxLayout(placeholder);
    layout->addWidget(_chartSpline_1);
    layout->addWidget(_chartSpline_2);
    placeholder->setLayout(layout);

    //设置具体阴影
    QGraphicsDropShadowEffect *shadow_effect1 = new QGraphicsDropShadowEffect(this);
    shadow_effect1->setOffset(0, 0);
    //阴影颜色
    shadow_effect1->setColor(QColor(38, 78, 119, 127));
    //阴影半径
    shadow_effect1->setBlurRadius(30);
    ui->headNevagationFrame->setGraphicsEffect(shadow_effect1);

    //设置具体阴影
    QGraphicsDropShadowEffect *shadow_effect2 = new QGraphicsDropShadowEffect(this);
    shadow_effect2->setOffset(0, 0);
    //阴影颜色
    shadow_effect2->setColor(QColor(38, 78, 119, 127));
    //阴影半径
    shadow_effect2->setBlurRadius(30);
    ui->siderBarFrame->setGraphicsEffect(shadow_effect2);

    QGraphicsDropShadowEffect *shadow_effect3 = new QGraphicsDropShadowEffect(this);
    shadow_effect3->setOffset(0, 0);
    //阴影颜色
    shadow_effect3->setColor(QColor(38, 78, 119, 127));
    //阴影半径
    shadow_effect3->setBlurRadius(30);
    ui->personageFrame->setGraphicsEffect(shadow_effect3);

    QGraphicsDropShadowEffect *shadow_effect4 = new QGraphicsDropShadowEffect(this);
    shadow_effect4->setOffset(0, 0);
    //阴影颜色
    shadow_effect4->setColor(QColor(38, 78, 119, 127));
    //阴影半径
    shadow_effect4->setBlurRadius(30);
    // ui->Chartsframe->setGraphicsEffect(shadow_effect4);


    connect(ui->firstbutton1,&QPushButton::clicked,this,[=](){
        ui->selectpage->setCurrentIndex(0);
    });

    connect(ui->MainCloseButton,&QPushButton::clicked,this,[=](){
        this->close();
    });

    connect(ui->stockbutton1,&QPushButton::clicked,this,[=](){
       ui->selectpage->setCurrentIndex(1);
    });

    connect(ui->rankbutton1,&QPushButton::clicked,this,[=](){
        ui->selectpage->setCurrentIndex(2);
    });

    connect(ui->dealbutton1,&QPushButton::clicked,this,[=](){
        ui->selectpage->setCurrentIndex(3);
    });

    connect(ui->communitybutton1,&QPushButton::clicked,this,[=](){
        forum* Forum=new forum();
        Forum->show();
    });

    connect(ui->leavebutton1,&QPushButton::clicked,this,[=](){
        this->close();
    });



    Personpage* person = new Personpage();
    connect(ui->ChargeButton, &QPushButton::clicked, person, &Personpage::openChargePage);
    connect(ui->personpageBtn,&QPushButton::clicked,[=](){person->show();});



    //时间初始化
    int userID = Global::instance().getGlobalUserManage()->GetUser(0)->GetId();
    Date currentDate(2023,Global::instance().getGlobalDataBase()->getTime(userID));
    if(currentDate.getMonth()>12){
        ui->timelabel->setText("模拟已结束");
    }
    else{
        QString dateString = QString("%1年%2月").arg(currentDate.getYear()).arg(currentDate.getMonth(), 2, 10, QChar('0'));
        ui->timelabel->setText(dateString);
    }
    QFont font = ui->timelabel->font();
    font.setPointSize(12);
    ui->timelabel->setFont(font);
    int monthss=currentDate.getMonth();


    if(monthss>12){
        ui->TransactionButton->setDisabled(true);
        ui->nextroundbutton->setDisabled(true);
    }


    //首页添加折线图
    // QVBoxLayout *layout_1 = new QVBoxLayout(ui->Chartsframe);
    ChartSpline* ch=new ChartSpline;
    // ui->Chartsframe->setLayout(layout_1);
    ui->MainChartsLayout->addWidget(ch);
    // ChartSpline* ch_2=new ChartSpline;

    // QVBoxLayout *layout_1 = new QVBoxLayout(ui->Chartsframe);
    // ChartSpline* ch=new ChartSpline;
    // ui->Chartsframe->setLayout(layout_1);
    // ui->MainChartsLayout->addWidget(ch);


    ui->selectpage1->setLayout(ui->Page1Layout);
    // Global::instance().getGlobalDataBase()->setTotalvalue(userID,totalcurrency(userID,currentDate.getMonth()));

    //排行榜
    std::vector<QString> userNames=Global::instance().getGlobalDataBase()->getAllUserName();
    std::vector<UserData> userData ;
    for (const QString& userName : userNames) {
        int userID=Global::instance().getGlobalDataBase()->getUserId(userName);
        int totalcurrency=Global::instance().getGlobalDataBase()->getTotalvalue(userID);
        int month=Global::instance().getGlobalDataBase()->getTime(userID);
        if(month>12){month--;}
        userData.emplace_back(userName,totalcurrency,month);
    }


    // 根据总资产排序
    std::sort(userData.begin(), userData.end(), compareByAssets);

    // // 创建表格
    // QTableWidget table(userData.size(), 3);
    // table.setHorizontalHeaderLabels(QStringList() << "User ID" << "Total Assets" << "Month");

    // 填充表格
    for (int i = 0; i < userData.size(); ++i) {

        ui->tableWidget->insertRow(i);
        QTableWidgetItem *idItem = new QTableWidgetItem(QString (userData[i].userName));
        QTableWidgetItem *assetsItem = new QTableWidgetItem(QString::number(userData[i].totalAssets));
        QTableWidgetItem *monthItem = new QTableWidgetItem(QString::number(userData[i].month));
        ui->tableWidget->setItem(i, 0, idItem);
        ui->tableWidget->setItem(i, 2, assetsItem);
        ui->tableWidget->setItem(i, 1, monthItem);
    }
// ui->tableWidget->resizeColumnToContents(4);
    // for(int i=0;i<4;i++)
    // {
        ui->tableWidget->resizeColumnsToContents();
    // }

    //新闻窗口

    NewsWidget *news = new NewsWidget(ui->selectpage1);
    ui->Page1Layout->addWidget(news);
    news->move(800,100);
    news->show();
    news->updateNews();

    // int year=Global::instance().getGlobalUserManage()->GetUser(0)->GetDate()->getYear();
    // int month=Global::instance().getGlobalDataBase().

    // this->resize(1213,700);
    // this->resize(1700,700);

    ui->selectpage2->setLayout(ui->stockTotalLayout);

    forumOpen = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_TransactionButton_clicked()
{
    buyin *buy = new buyin();
    buy->show();
}


void MainWindow::on_nextroundbutton_clicked()
{
    int userID = Global::instance().getGlobalUserManage()->GetUser(0)->GetId();
    int months=Global::instance().getGlobalDataBase()->getTime(userID);
    Date currentDate(2023,months);



    std::vector<Record> records = Global::instance().getGlobalDataBase()->getUserRecord(userID);
    bool found = false;
   for (Record record : records) {

        QString fromPosition = record.GetDate().mid(5,2);

        bool ok;
        int month = fromPosition.toInt(&ok);

            if (month ==currentDate.getMonth() ) {
                found = true;
                qDebug()<<month<<"lzy";
                break; // 如果找到，可以立即退出循环
            }

    }
   if(months==12){
       QMessageBox msg(QMessageBox::Question,"结束","本次模拟已结束,感谢您的参与",QMessageBox::Yes | QMessageBox::No,this);
       msg.exec();
       currentDate.addMonths(1);
       Global::instance().getGlobalDataBase()->setTime(userID,currentDate.getMonth());
       ui->timelabel->setText("模拟已结束");
       ui->TransactionButton->setDisabled(true);
       ui->nextroundbutton->setDisabled(true);
   }
   else{
       if (found) {QMessageBox msg(QMessageBox::Question,"提示","是否进行到下一轮操作?",QMessageBox::Yes | QMessageBox::No,this);
        int ret = msg.exec();
        if(ret==QMessageBox::Yes)
        {
            currentDate.addMonths(1);
            Global::instance().getGlobalDataBase()->setTime(userID,currentDate.getMonth());
            ui->timelabel->setText(QString("%1年%2月").arg(currentDate.getYear()).arg(currentDate.getMonth()));

            buyin buyini;
            buyini.setBuyInInfo();
            buyini.setSellOutInfo();

            Global::instance().getGlobalDataBase()->setTotalvalue(userID,totalcurrency(userID,months));

            NewsWidget news2;
            MainWindow* main= new MainWindow();
            this->close();
            news2.updateNews();
            main->show();
        }}
    else{QMessageBox msg(QMessageBox::Question,"提示","您本轮还没有进行任何操作，是否进行到下一轮操作?",QMessageBox::Yes | QMessageBox::No,this);
        int ret = msg.exec();
        if(ret==QMessageBox::Yes)
        {
            currentDate.addMonths(1);
            Global::instance().getGlobalDataBase()->setTime(userID,currentDate.getMonth());
            ui->timelabel->setText(QString("%1年%2月").arg(currentDate.getYear()).arg(currentDate.getMonth()));

            buyin buyini;
            buyini.setBuyInInfo();
            buyini.setSellOutInfo();

            Global::instance().getGlobalDataBase()->setTotalvalue(userID,totalcurrency(userID,months));

            NewsWidget news2;
            MainWindow* main= new MainWindow();
            this->close();
            news2.updateNews();
            main->show();
        }}}
}

int MainWindow::totalcurrency(int userID,int months){
    // int userID = Global::instance().getGlobalUserManage()->GetUser(0)->GetId();
    // int months=Global::instance().getGlobalDataBase()->getTime(userID);
    Date currentDate(2023,months);

    int activecurrency=Global::instance().getGlobalDataBase()->GetBalance(userID);

    std::vector<long>& stockInfo1 = Global::instance().getGlobalDataBase()->getStockInfo(1, 2023, currentDate.getMonth());
    long stockPrice1 = stockInfo1[0]; // 获取股票价格
    std::cout << "Stock Price: " << stockPrice1 << std::endl;
    int number1=Global::instance().getGlobalDataBase()->getUserVolume(userID,1);
    int stockcurrency1=stockPrice1*number1;

    std::vector<long>& stockInfo2 = Global::instance().getGlobalDataBase()->getStockInfo(2, 2023, currentDate.getMonth());
    long stockPrice2 = stockInfo2[0]; // 获取股票价格
    std::cout << "Stock Price: " << stockPrice2 << std::endl;
    int number2=Global::instance().getGlobalDataBase()->getUserVolume(userID,2);
    int stockcurrency2=stockPrice2*number2;

    std::vector<long>& stockInfo3 = Global::instance().getGlobalDataBase()->getStockInfo(3, 2023, currentDate.getMonth());
    long stockPrice3 = stockInfo3[0]; // 获取股票价格
    std::cout << "Stock Price: " << stockPrice3 << std::endl;
    int number3=Global::instance().getGlobalDataBase()->getUserVolume(userID,3);
    int stockcurrency3=stockPrice3*number3;

    std::vector<long>& stockInfo4 = Global::instance().getGlobalDataBase()->getStockInfo(4, 2023, currentDate.getMonth());
    long stockPrice4 = stockInfo4[0]; // 获取股票价格
    std::cout << "Stock Price: " << stockPrice4 << std::endl;
    int number4=Global::instance().getGlobalDataBase()->getUserVolume(userID,4);
    int stockcurrency4=stockPrice4*number4;

    std::vector<long>& stockInfo5 = Global::instance().getGlobalDataBase()->getStockInfo(5, 2023, currentDate.getMonth());
    long stockPrice5 = stockInfo5[0]; // 获取股票价格
    std::cout << "Stock Price: " << stockPrice5 << std::endl;
    int number5=Global::instance().getGlobalDataBase()->getUserVolume(userID,5);
    int stockcurrency5=stockPrice5*number5;

    std::vector<long>& stockInfo6 = Global::instance().getGlobalDataBase()->getStockInfo(6, 2023, currentDate.getMonth());
    long stockPrice6 = stockInfo6[0]; // 获取股票价格
    std::cout << "Stock Price: " << stockPrice6 << std::endl;
    int number6=Global::instance().getGlobalDataBase()->getUserVolume(userID,6);
    int stockcurrency6=stockPrice6*number6;

    std::vector<long>& stockInfo7 = Global::instance().getGlobalDataBase()->getStockInfo(7, 2023, currentDate.getMonth());
    long stockPrice7 = stockInfo7[0]; // 获取股票价格
    std::cout << "Stock Price: " << stockPrice7 << std::endl;
    int number7=Global::instance().getGlobalDataBase()->getUserVolume(userID,7);
    int stockcurrency7=stockPrice7*number7;

    std::vector<long>& stockInfo8 = Global::instance().getGlobalDataBase()->getStockInfo(8, 2023, currentDate.getMonth());
    long stockPrice8 = stockInfo8[0]; // 获取股票价格
    std::cout << "Stock Price: " << stockPrice8 << std::endl;
    int number8=Global::instance().getGlobalDataBase()->getUserVolume(userID,8);
    int stockcurrency8=stockPrice8*number8;

    int totalcurrency=activecurrency+stockcurrency1+stockcurrency2+stockcurrency3+stockcurrency4+stockcurrency5+stockcurrency6+stockcurrency7+stockcurrency8;
    qDebug()<<"totalcurrency"<<totalcurrency;
    return totalcurrency;
}


void MainWindow::on_communitybutton1_clicked()
{

}

void MainWindow::mousePressEvent(QMouseEvent *event){

    if( (event->button() == Qt::LeftButton) ){
        mouse_press = true;
        mousePoint = event->globalPos() - this->pos();
        //        event->accept();
    }
    else if(event->button() == Qt::RightButton){
        //如果是右键
        this->close();

    }

}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    if(mouse_press){
        move(event->globalPos() - mousePoint);

    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    mouse_press = false;
}
