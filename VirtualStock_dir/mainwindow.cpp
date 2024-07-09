#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chartspline.h"
#include <QPlainTextEdit>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    ui->selectpage4->setLayout(ui->RuleLayout);//规则介绍布局问题
    ui->selectpage->setCurrentIndex(0);
    //将页面切换逻辑使用按钮的click进行手动转换

    ui->TransactionRule->setReadOnly(1);

    //尝试将股票的信息挂载到股票界面的layout中
    // 找到占位部件
    ChartSpline *_chartSpline=new ChartSpline;
    _chartSpline->ChangeStock(0);
    connect(ui->ChangeStockShowBtn, &QPushButton::clicked, _chartSpline, &ChartSpline::ShowRandomStock);
    // 在股票界面设置显示哪一只股票
    connect(ui->ChooseWhichStock, QOverload<int>::of(&QComboBox::currentIndexChanged),
            _chartSpline, &ChartSpline::ChangeStock);

    QWidget *placeholder = ui->chartSplineWidget;

    this->resize(1213,700);
    // 设置 chartspline 对象到占位部件的位置
    QVBoxLayout *layout = new QVBoxLayout(placeholder);
    layout->addWidget(_chartSpline);
    placeholder->setLayout(layout);


    connect(ui->firstbutton1,&QPushButton::clicked,this,[=](){
        ui->selectpage->setCurrentIndex(0);
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
        ui->selectpage->setCurrentIndex(4);
    });

    connect(ui->leavebutton1,&QPushButton::clicked,this,[=](){
        this->close();
    });
    int userID = Global::instance().getGlobalUserManage()->GetUser(0)->GetId();
    Date currentDate(2023,Global::instance().getGlobalDataBase()->getTime(userID));
    QString dateString = QString("%1年%2月").arg(currentDate.getYear()).arg(currentDate.getMonth(), 2, 10, QChar('0'));
    ui->timelabel->setText(dateString);
    QFont font = ui->timelabel->font();
    font.setPointSize(12);
    ui->timelabel->setFont(font);


    NewsWidget *news = new NewsWidget(ui->selectpage1);
    news->move(750,150);
    news->show();

    // int year=Global::instance().getGlobalUserManage()->GetUser(0)->GetDate()->getYear();
    // int month=Global::instance().getGlobalDataBase().



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buyinButton_clicked()
{
    buyin *buy = new buyin();
    buy->show();
}


void MainWindow::on_personpage1_clicked()
{
    Personpage* person = new Personpage();
    person->show();
}


void MainWindow::on_nextroundbutton_clicked()
{
    int userID = Global::instance().getGlobalUserManage()->GetUser(0)->GetId();
    Date currentDate(2023,Global::instance().getGlobalDataBase()->getTime(userID));
    QMessageBox msg(QMessageBox::Question,"提示","您本轮还没有进行任何操作，是否进行到下一轮操作?",QMessageBox::Yes | QMessageBox::No,this);
    int ret = msg.exec();
    if(ret==QMessageBox::Yes)
    {
        currentDate.addMonths(1);
        Global::instance().getGlobalDataBase()->setTime(userID,currentDate.getMonth());
        ui->timelabel->setText(QString("%1年%2月").arg(currentDate.getYear()).arg(currentDate.getMonth()));
        buyin buyini;
        buyini.setBuyInInfo();
    }

}




void MainWindow::on_communitybutton1_clicked()
{
    forum* Forum=new forum();
    Forum->show();
}

