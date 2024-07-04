#include "mainwindow.h"
#include "ui_buyin.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include<personpage.h>
#include "login.h"
MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->firstbutton1,&QPushButton::clicked,this,[=](){
        ui->selectpage->setCurrentIndex(0);
    });

    connect(ui->stockbutton1,&QPushButton::clicked,this,[=](){
       ui->selectpage->setCurrentIndex(1);
    });

    connect(ui->dealbutton1,&QPushButton::clicked,this,[=](){
        ui->selectpage->setCurrentIndex(3);
    });
    connect(ui->rankbutton1,&QPushButton::clicked,this,[=](){
       ui->selectpage->setCurrentIndex(2);
    });

    connect(ui->communitybutton1,&QPushButton::clicked,this,[=](){
       ui->selectpage->setCurrentIndex(4);
    });
    connect(ui->leavebutton1,&QPushButton::clicked,this,[=](){
        this->close();
    });


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    this->close();
    buyin *buy = new buyin();
    buy->show();
}

    
void MainWindow::on_personpage2_clicked()
{
    personpage *Personpage=new personpage;
    Personpage->show();
    this->close();

}


void MainWindow::on_pushButton_2_clicked()
{
    this->close();
    buyin *buy = new buyin();
    buy->show();
    buy->ui->stackedWidget->setCurrentIndex(1);
}
void MainWindow::on_pushButton_3_clicked()
{
    this->close();
    buyin *buy = new buyin();
    buy->show();
    buy->ui->stackedWidget->setCurrentIndex(2);
}
void MainWindow::on_pushButton_4_clicked()
{
    this->close();
    buyin *buy = new buyin();
    buy->show();
    buy->ui->stackedWidget->setCurrentIndex(3);
}
void MainWindow::on_pushButton_5_clicked()
{
    this->close();
    buyin *buy = new buyin();
    buy->show();
    buy->ui->stackedWidget->setCurrentIndex(4);
}
void MainWindow::on_pushButton_6_clicked()
{
    this->close();
    buyin *buy = new buyin();
    buy->show();
    buy->ui->stackedWidget->setCurrentIndex(5);
}


void MainWindow::on_leavebutton1_clicked()
{
    Login* log =new Login();
    log->show();
    this->close();
}

