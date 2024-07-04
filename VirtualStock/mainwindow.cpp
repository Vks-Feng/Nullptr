#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include<personpage.h>
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

void MainWindow::on_personpage2_clicked()
{
    personpage *Personpage=new personpage;
    Personpage->show();
    this->close();

}

