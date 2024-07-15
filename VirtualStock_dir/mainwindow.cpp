#include "mainwindow.h"
#include "ui_mainwindow.h"

struct UserData {
    QString userName;
    double totalAssets;
    int month;
    double totalAssetsrate;
    UserData(const QString& userName, double totalAssets , int month, double totalAssetsrate )
        : userName(userName), totalAssets(totalAssets), month(month) ,totalAssetsrate(totalAssetsrate){}
};

bool compareByAssets(const UserData &a, const UserData &b) {
    return a.totalAssets > b.totalAssets; // 降序排序
}
MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);


    //主窗口设置阴影、圆角化
    // setAttribute(Qt::WA_TranslucentBackground);//透明化
    this->setWindowFlags(Qt::FramelessWindowHint);//无边框

    //毛玻璃实现；浮在widget表面，失败
    // ui->selectpage->setParent(ui->frame_3);
    // ui->selectpage->setAttribute(Qt::WA_TranslucentBackground, false);
    // ui->selectpage->raise();  // 手动提升 ui->selectpage 控件的层级
    // QGraphicsBlurEffect *blur = new QGraphicsBlurEffect(ui->selectpage);
    // blur->setBlurRadius(10);
    // ui->selectpage->setGraphicsEffect(blur);
    // ui->selectpage->setAttribute(Qt::WA_TranslucentBackground,true);

    //添加buyin
    buyin_widget=new buyin;
    forum_widget = new forum;
    ui->selectpage5_forum->setLayout(ui->Forum_layout);
    ui->Forum_layout->addWidget(forum_widget);

//    // 遍历所有子对象
//    foreach (QObject *child, buyin_widget->children()) {
//        QPushButton *button = qobject_cast<QPushButton *>(child);
//        if (button) {
//            button->setFlat(false);
//        }
//    }
    ui->selectpage6_trade->setLayout(ui->Trade_layout);
    ui->Trade_layout->addWidget(buyin_widget);


    //添加forum
    refreshForum();
    connect(Global::instance().getGlobalClient(), &ClientSocket::signal_Receive_Refresh, this, &MainWindow::refreshForum);

//    // 遍历所有子对象
//    foreach (QObject *child, forum_widget->children()) {
//        QPushButton *button = qobject_cast<QPushButton *>(child);
//        if (button) {
//            button->setFlat(false);
//        }
//    }




    ui->logo->setScaledContents(true);//logo自适应大小


    ui->selectpage4->setLayout(ui->RuleLayout);//规则介绍布局问题
    ui->selectpage->setCurrentIndex(0);//将页面切换逻辑使用按钮的click进行手动转换
    ui->TransactionRule->setReadOnly(1);

    //固定大小
    this->setFixedSize(this->width(),this->height());

    //设置Frame具体阴影
    // QGraphicsDropShadowEffect *shadow_effect1 = new QGraphicsDropShadowEffect(this);
    // shadow_effect1->setOffset(0, 0);
    // shadow_effect1->setColor(QColor(38, 78, 119, 127)); //阴影颜色
    // shadow_effect1->setBlurRadius(30);//阴影半径
    // ui->headNevagationFrame->setGraphicsEffect(shadow_effect1);
    //侧导航栏阴影
    // QGraphicsDropShadowEffect *shadow_effect2 = new QGraphicsDropShadowEffect(this);
    // shadow_effect2->setOffset(0, 0);
    // shadow_effect2->setColor(QColor(38, 78, 119, 127));
    // shadow_effect2->setBlurRadius(30);
    // ui->siderBarFrame->setGraphicsEffect(shadow_effect2);
    //首页个人模块阴影
    QGraphicsDropShadowEffect *shadow_effect3 = new QGraphicsDropShadowEffect(this);
    shadow_effect3->setOffset(0, 0);
    shadow_effect3->setColor(QColor(38, 78, 119, 127));
    shadow_effect3->setBlurRadius(30);
    ui->personageFrame->setGraphicsEffect(shadow_effect3);
    //首页表格模块阴影
    QGraphicsDropShadowEffect *shadow_effect4 = new QGraphicsDropShadowEffect(this);
    shadow_effect4->setOffset(0, 0);
    shadow_effect4->setColor(QColor(38, 78, 119, 127));
    shadow_effect4->setBlurRadius(30);
    ui->chartsFrame->setGraphicsEffect(shadow_effect4);
    //另外两个frame
    // QGraphicsDropShadowEffect *shadow_effect5 = new QGraphicsDropShadowEffect(this);
    // shadow_effect5->setOffset(0, 0);
    // shadow_effect5->setColor(QColor(38, 78, 119, 127));
    // shadow_effect5->setBlurRadius(30);
    // ui->Homeframe1->setGraphicsEffect(shadow_effect5);
    // QGraphicsDropShadowEffect *shadow_effect6 = new QGraphicsDropShadowEffect(this);
    // shadow_effect6->setOffset(0, 0);
    // shadow_effect6->setColor(QColor(38, 78, 119, 127));
    // shadow_effect6->setBlurRadius(30);
    // ui->RuleFrame->setGraphicsEffect(shadow_effect6);

    //stockPage页面设置阴影
    QGraphicsDropShadowEffect *shadow_effect7= new QGraphicsDropShadowEffect(this);
    shadow_effect7->setOffset(0, 0);
    shadow_effect7->setColor(QColor(38, 78, 119, 127)); //阴影颜色
    shadow_effect7->setBlurRadius(30);//阴影半径
    ui->StockWidget_1->setGraphicsEffect(shadow_effect7);

    QGraphicsDropShadowEffect *shadow_effect8= new QGraphicsDropShadowEffect(this);
    shadow_effect8->setOffset(0, 0);
    shadow_effect8->setColor(QColor(38, 78, 119, 127)); //阴影颜色
    shadow_effect8->setBlurRadius(30);//阴影半径
    ui->StockWidget_2->setGraphicsEffect(shadow_effect8);

    QGraphicsDropShadowEffect *shadow_effect9= new QGraphicsDropShadowEffect(this);
    shadow_effect9->setOffset(0, 0);
    shadow_effect9->setColor(QColor(38, 78, 119, 127)); //阴影颜色
    shadow_effect9->setBlurRadius(30);//阴影半径
    ui->stockIntro_1->setGraphicsEffect(shadow_effect9);

    QGraphicsDropShadowEffect *shadow_effect10= new QGraphicsDropShadowEffect(this);
    shadow_effect10->setOffset(0, 0);
    shadow_effect10->setColor(QColor(38, 78, 119, 127)); //阴影颜色
    shadow_effect10->setBlurRadius(30);//阴影半径
    ui->stockIntro_2->setGraphicsEffect(shadow_effect10);


    //设置跳转的槽函数
    connect(ui->Minimum_Button,&QPushButton::clicked,this,[=](){
        this->showMinimized();
    });

    connect(ui->MainCloseButton,&QPushButton::clicked,this,[=](){
        this->close();
    });

    connect(ui->firstbutton1,&QPushButton::clicked,this,[=](){
        ui->selectpage->setCurrentIndex(0);
    });

    connect(ui->stockbutton1,&QPushButton::clicked,this,[=](){
       ui->selectpage->setCurrentIndex(1);
    });

    connect(ui->TransactionButton,&QPushButton::clicked,this,[=](){
        buyin_widget->initBuyInSellOut();
        ui->selectpage->setCurrentIndex(2);
    });//点击跳转到交易界面

    connect(ui->communitybutton1,&QPushButton::clicked,this,[=](){
        ui->selectpage->setCurrentIndex(5);
    });//点击跳转到社区交流界面

    connect(ui->rankbutton1,&QPushButton::clicked,this,[=](){
        ui->userRankingList->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->userRankingList->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->selectpage->setCurrentIndex(3);
    });

    connect(ui->dealbutton1,&QPushButton::clicked,this,[=](){
        ui->selectpage->setCurrentIndex(4);
    });

    connect(ui->leavebutton1,&QPushButton::clicked,this,[=](){
        this->close();
    });

    Personpage* person = new Personpage();
    //需要解决个人主页点击不初始化的问题
    connect(ui->ChargeButton, &QPushButton::clicked, person, &Personpage::openChargePage);
    connect(ui->personpageBtn,&QPushButton::clicked,[=](){
        Personpage* aperson = new Personpage();
        aperson->show();
    });

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
    ChartSpline* ch=new ChartSpline;
    ui->MainChartsLayout->addWidget(ch);
    ui->selectpage1->setLayout(ui->Page1Layout);
    // Global::instance().getGlobalDataBase()->setTotalvalue(userID,totalcurrency(userID,currentDate.getMonth()));


    //股票界面相关
    //尝试将股票的信息挂载到股票界面的layout中
    // 找到占位部件
    ChartSpline *_chartSpline_1=new ChartSpline;
    ChartSpline *_chartSpline_2=new ChartSpline;

    _chartSpline_1->ChangeStock(0);
    _chartSpline_2->ChangeStock(1);
    PutCompanyName_1(0);
    PutCompanyName_2(1);
    ui->stockIntro_1->setReadOnly(true);
    ui->stockIntro_1->setReadOnly(true);

    //    connect(ui->ChangeStockShowBtn, &QPushButton::clicked, _chartSpline, &ChartSpline::ShowRandomStock);
    // 在股票界面设置显示哪一只股票
    // 随机显示一家公司的股票

    connect(ui->ChooseWhichStock_1, QOverload<int>::of(&QComboBox::currentIndexChanged),
            _chartSpline_1, &ChartSpline::ChangeStock);

    connect(ui->ChooseWhichStock_2, QOverload<int>::of(&QComboBox::currentIndexChanged),
            _chartSpline_2, &ChartSpline::ChangeStock);

    connect(ui->ChooseWhichStock_1, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::PutCompanyName_1);

    connect(ui->ChooseWhichStock_2, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this,&MainWindow::PutCompanyName_2);

    ui->ChooseWhichStock_2->setCurrentIndex(1);

    QWidget *placeholder_1 = ui->StockWidget_1;
    QWidget *placeholder_2 = ui->StockWidget_2;

    // 设置 chartspline 对象到占位部件的位置
    QVBoxLayout *layout_1 = new QVBoxLayout(placeholder_1);
    QVBoxLayout *layout_2 = new QVBoxLayout(placeholder_2);
    layout_1->addWidget(_chartSpline_1);
    layout_2->addWidget(_chartSpline_2);
    //    placeholder->setLayout(layout);

    //排行榜
    std::vector<QString> userNames=Global::instance().getGlobalDataBase()->getAllUserName();
    std::vector<UserData> userData ;
    for (const QString& userName : userNames) {
        int userID=Global::instance().getGlobalDataBase()->getUserId(userName);
        int totalcurrency=Global::instance().getGlobalDataBase()->getTotalvalue(userID);
        int month=Global::instance().getGlobalDataBase()->getTime(userID);
        double totalrate=100*(totalcurrency-64800)/64800;
        if(month>12){month--;}
        userData.emplace_back(userName,totalcurrency,month,totalrate);
    }


    // 根据总资产排序
    std::sort(userData.begin(), userData.end(), compareByAssets);

    // // 创建表格
    // QTableWidget table(userData.size(), 3);
    // table.setHorizontalHeaderLabels(QStringList() << "User ID" << "Total Assets" << "Month");

    // 填充表格
    for (int i = 0; i < userData.size(); ++i) {

        ui->userRankingList->insertRow(i);
        QString percentageString = QString::number(userData[i].totalAssetsrate) + "%";
        QTableWidgetItem *idItem = new QTableWidgetItem(QString (userData[i].userName));
        QTableWidgetItem *assetsItem = new QTableWidgetItem(QString::number(userData[i].totalAssets));
        QTableWidgetItem *monthItem = new QTableWidgetItem(QString::number(userData[i].month));
        QTableWidgetItem *percentItem = new QTableWidgetItem(QString (percentageString));
        ui->userRankingList->setItem(i, 0, idItem);
        ui->userRankingList->setItem(i, 2, assetsItem);
        ui->userRankingList->setItem(i, 1, monthItem);
        ui->userRankingList->setItem(i, 3, percentItem);
        Global::instance().getGlobalDataBase()->setRanking(Global::instance().getGlobalDataBase()->getUserId(userData[i].userName),i+1);
    }
// ui->tableWidget->resizeColumnToContents(4);
    // for(int i=0;i<4;i++)
    // {
     ui->userRankingList->resizeColumnsToContents();
    // }

    //新闻窗口

    NewsWidget *news = new NewsWidget(ui->selectpage1);
    ui->Page1Layout->addWidget(news);
    news->move(800,100);
    news->show();
    news->updateNews();
}

MainWindow::~MainWindow()
{
    Global::instance().getGlobalDataBase()->close();//关闭数据库
    delete ui;
}

QString MainWindow::CompanyIntro(int index)
{
    QStringList company_profiles = {
        "Apple Inc. (AAPL):\n"
        "简介: 苹果公司成立于1976年，总部位于加利福尼亚州库比蒂诺。公司设计、开发和销售消费电子、计算机软件和在线服务。其知名产品包括 iPhone 智能手机、iPad 平板电脑、Mac 电脑、Apple Watch 智能手表和 Apple TV。苹果以其创新设计和高质量产品闻名。\n"
        "股票相关: 苹果公司的股票在纳斯达克交易所上市，股票代码为 AAPL。苹果是全球市值最高的公司之一，吸引了大量投资者。该公司定期派发股息，并通过股票回购计划来增加股东价值。",

        "Amazon.com, Inc. (AMZN):\n"
        "简介: 亚马逊公司成立于1994年，总部位于华盛顿州西雅图。公司专注于电子商务、云计算、数字流媒体和人工智能。其业务涵盖广泛，包括在线零售、AWS（亚马逊网络服务）、Prime 会员服务和 Alexa 智能助手。\n"
        "股票相关: 亚马逊公司的股票在纳斯达克交易所上市，股票代码为 AMZN。亚马逊是全球市值最高的公司之一，拥有强劲的增长前景和庞大的用户基础。尽管公司不定期派发股息，但其股票价格增长潜力吸引了许多投资者。",

        "Alphabet Inc. (GOOGL):\n"
        "简介: Alphabet Inc. 是谷歌的母公司，成立于2015年。谷歌是一家美国跨国科技公司，总部位于加利福尼亚州山景城，主要提供互联网相关的产品和服务，包括搜索引擎、在线广告、云计算和软件开发。公司的核心产品包括 Google Search、YouTube、Android 和 Google Cloud。\n"
        "股票相关: Alphabet Inc. 的股票在纳斯达克交易所上市，分为两类：A 类普通股（股票代码 GOOGL）和 C 类普通股（股票代码 GOOG）。公司不派发股息，主要通过股票价格增长和公司业务扩展来回报股东。",

        "International Business Machines Corporation (IBM):\n"
        "简介: IBM 成立于1911年，总部位于纽约州阿蒙克。公司主要提供硬件、软件、云计算和人工智能解决方案。IBM 以其创新和研究实力著称，产品和服务涵盖从大型机到人工智能 Watson、区块链和混合云等多个领域。\n"
        "股票相关: IBM 的股票在纽约证券交易所上市，股票代码为 IBM。公司定期派发股息，是投资者稳定收益的选择之一。尽管近年来公司面临挑战，但其转型战略和技术创新使其仍具投资吸引力。",

        "Intel Corporation (INTC):\n"
        "简介: 英特尔公司成立于1968年，总部位于加利福尼亚州圣克拉拉。公司主要设计和制造半导体芯片，是全球最大的半导体芯片制造商之一。其产品广泛应用于计算机和其他电子设备中，包括处理器、存储设备和网络接口。\n"
        "股票相关: 英特尔公司的股票在纳斯达克交易所上市，股票代码为 INTC。公司定期派发股息，并通过股票回购计划增加股东价值。英特尔在半导体行业中的领导地位使其成为长期投资的选择之一。",

        "JetBlue Airways Corporation (JBLU):\n"
        "简介: 捷蓝航空公司成立于1998年，总部位于纽约市。公司提供主要在美国境内以及加勒比地区的航班服务，以其低票价和高服务质量著称。捷蓝航空以其创新的客户服务和舒适的飞行体验赢得了大量忠实客户。\n"
        "股票相关: 捷蓝航空公司的股票在纳斯达克交易所上市，股票代码为 JBLU。尽管航空业具有波动性，但公司稳定的市场份额和客户基础使其股票具有一定的投资价值。",

        "Meta Platforms, Inc. (META):\n"
        "简介: Meta Platforms, Inc. 原名 Facebook, Inc.，成立于2004年，总部位于加利福尼亚州门洛帕克。公司主要提供社交媒体和社交网络服务，包括 Facebook、Instagram、WhatsApp 和 Oculus 等产品。Meta 专注于增强现实和虚拟现实技术的开发和应用。\n"
        "股票相关: Meta 的股票在纳斯达克交易所上市，股票代码为 META。公司不派发股息，主要通过强劲的收入增长和技术创新来回报股东。Meta 在全球社交媒体领域的领导地位和不断扩展的技术前景使其成为投资者关注的焦点。",

        "Microsoft Corporation (MSFT):\n"
        "简介: 微软公司成立于1975年，总部位于华盛顿州雷德蒙德。公司主要开发、制造、许可和销售计算机软件、消费电子、个人计算机和相关服务。其知名产品包括 Windows 操作系统、Office 办公软件套件和 Azure 云计算平台。微软在企业和个人计算领域具有强大的市场影响力。\n"
        "股票相关: 微软公司的股票在纳斯达克交易所上市，股票代码为 MSFT。公司定期派发股息，并通过股票回购计划增加股东价值。微软的强劲财务表现和持续创新能力使其成为稳健的投资选择。",

        "Tesla, Inc. (TSLA):\n"
        "简介: 特斯拉公司成立于2003年，总部位于加利福尼亚州帕洛阿尔托。公司主要设计、制造和销售电动汽车、电池储能系统和太阳能产品。特斯拉以其创新和环保科技著称，其产品包括 Model S、Model 3、Model X 和 Model Y 电动汽车，以及 Powerwall 和 Solar Roof 等能源解决方案。\n"
        "股票相关: 特斯拉公司的股票在纳斯达克交易所上市，股票代码为 TSLA。特斯拉以其高增长潜力吸引了大量投资者，公司不定期派发股息，主要通过股票价格的快速增长回报股东。特斯拉在电动汽车和清洁能源领域的领先地位使其成为投资者关注的重点。"


    };
    return company_profiles[index];
}

void MainWindow::PutCompanyName_1(int index)
{
    ui->stockIntro_1->setPlainText(CompanyIntro(index));
}

void MainWindow::PutCompanyName_2(int index)
{
    ui->stockIntro_2->setPlainText(CompanyIntro(index));
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

            Global::instance().getGlobalDataBase()->setTotalvalue(userID,totalcurrency(userID,currentDate.getMonth()+1));

            NewsWidget news2;
            MainWindow* main= new MainWindow();
            this->close();
            news2.updateNews();
            main->show();
            showCustomDialog();
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
            showCustomDialog();

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
    if(number1==-1){number1++;}
    int stockcurrency1=stockPrice1*number1;

    std::vector<long>& stockInfo2 = Global::instance().getGlobalDataBase()->getStockInfo(2, 2023, currentDate.getMonth());
    long stockPrice2 = stockInfo2[0]; // 获取股票价格
    std::cout << "Stock Price: " << stockPrice2 << std::endl;
    int number2=Global::instance().getGlobalDataBase()->getUserVolume(userID,2);
    if(number2==-1){number2++;}
    int stockcurrency2=stockPrice2*number2;

    std::vector<long>& stockInfo3 = Global::instance().getGlobalDataBase()->getStockInfo(3, 2023, currentDate.getMonth());
    long stockPrice3 = stockInfo3[0]; // 获取股票价格
    std::cout << "Stock Price: " << stockPrice3 << std::endl;
    int number3=Global::instance().getGlobalDataBase()->getUserVolume(userID,3);
    if(number3==-1){number3++;}
    int stockcurrency3=stockPrice3*number3;

    std::vector<long>& stockInfo4 = Global::instance().getGlobalDataBase()->getStockInfo(4, 2023, currentDate.getMonth());
    long stockPrice4 = stockInfo4[0]; // 获取股票价格
    std::cout << "Stock Price: " << stockPrice4 << std::endl;
    int number4=Global::instance().getGlobalDataBase()->getUserVolume(userID,4);
    if(number4==-1){number4++;}
    int stockcurrency4=stockPrice4*number4;

    std::vector<long>& stockInfo5 = Global::instance().getGlobalDataBase()->getStockInfo(5, 2023, currentDate.getMonth());
    long stockPrice5 = stockInfo5[0]; // 获取股票价格
    std::cout << "Stock Price: " << stockPrice5 << std::endl;
    int number5=Global::instance().getGlobalDataBase()->getUserVolume(userID,5);
    if(number5==-1){number5++;}
    int stockcurrency5=stockPrice5*number5;

    std::vector<long>& stockInfo6 = Global::instance().getGlobalDataBase()->getStockInfo(6, 2023, currentDate.getMonth());
    long stockPrice6 = stockInfo6[0]; // 获取股票价格
    std::cout << "Stock Price: " << stockPrice6 << std::endl;
    int number6=Global::instance().getGlobalDataBase()->getUserVolume(userID,6);
    if(number6==-1){number6++;}
    int stockcurrency6=stockPrice6*number6;

    std::vector<long>& stockInfo7 = Global::instance().getGlobalDataBase()->getStockInfo(7, 2023, currentDate.getMonth());
    long stockPrice7 = stockInfo7[0]; // 获取股票价格
    std::cout << "Stock Price: " << stockPrice7 << std::endl;
    int number7=Global::instance().getGlobalDataBase()->getUserVolume(userID,7);
    if(number7==-1){number7++;}
    int stockcurrency7=stockPrice7*number7;

    std::vector<long>& stockInfo8 = Global::instance().getGlobalDataBase()->getStockInfo(8, 2023, currentDate.getMonth());
    long stockPrice8 = stockInfo8[0]; // 获取股票价格
    std::cout << "Stock Price: " << stockPrice8 << std::endl;
    int number8=Global::instance().getGlobalDataBase()->getUserVolume(userID,8);
    if(number8==-1){number8++;}
    int stockcurrency8=stockPrice8*number8;

    int totalcurrency=activecurrency+stockcurrency1+stockcurrency2+stockcurrency3+stockcurrency4+stockcurrency5+stockcurrency6+stockcurrency7+stockcurrency8;
    qDebug()<<"totalcurrency"<<totalcurrency;
    return totalcurrency;
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

void MainWindow::refreshForum(){
    ui->Forum_layout->removeWidget(forum_widget);
    forum_widget = new forum;
    ui->selectpage5_forum->setLayout(ui->Forum_layout);
    ui->Forum_layout->addWidget(forum_widget);
}

void MainWindow::showCustomDialog() {
    dialog dialog1;
    dialog1.exec();
}



// void MainWindow::paintEvent(QPaintEvent *event)
// {
//     QPainter painter(this);
//     painter.setRenderHint(QPainter::Antialiasing);

//     QPainterPath path;
//     path.addRoundedRect(rect(),10,10);
//     painter.setClipPath(path);
//     painter.fillPath(path,Qt::white);

//     this->paintEvent(event);
// }


// void MainWindow::paintEvent(QPaintEvent *event)
// {
//     QPainter custompainter(this);
//     custompainter.setRenderHint(QPainter::Antialiasing, true);
//     QPainterPath path;
//     path.addRoundedRect(rect(),25,25);
//     QRegion maskRegion(path.toFillPolygon().toPolygon());
//     setMask(maskRegion);

//     custompainter.fillRect(rect(),Qt::white);

// }

