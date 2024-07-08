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

    //尝试将股票的信息挂载到股票界面的layout中
    // 找到占位部件

    ChartSpline *_chartSpline=new ChartSpline;
    connect(ui->ChangeStockShowBtn, &QPushButton::clicked, _chartSpline, &ChartSpline::ShowRandomStock);

    QWidget *placeholder = ui->chartSplineWidget;

    this->resize(1213,700);
    // 设置 chartspline 对象到占位部件的位置
    QVBoxLayout *layout = new QVBoxLayout(placeholder);
    layout->addWidget(_chartSpline);
    placeholder->setLayout(layout);

    NewsWidget *news = new NewsWidget(this);
    news->move(750,150);
    news->show();

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

