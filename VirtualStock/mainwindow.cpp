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
        ui->selectpage1->close();
        ui->selectpage1->show();
    });
    connect(ui->firstbutton2,&QPushButton::clicked,this,[=](){
        ui->selectpage2->close();
        ui->selectpage1->show();
    });
    connect(ui->firstbutton3,&QPushButton::clicked,this,[=](){
        ui->selectpage3->close();
        ui->selectpage1->show();
    });
    connect(ui->firstbutton4,&QPushButton::clicked,this,[=](){
        ui->selectpage4->close();
        ui->selectpage1->show();
    });
    connect(ui->firstbutton5,&QPushButton::clicked,this,[=](){
        ui->selectpage5->close();
        ui->selectpage1->show();
    });
    connect(ui->stockbutton1,&QPushButton::clicked,this,[=](){
        ui->selectpage1->close();
        ui->selectpage2->show();
    });
    connect(ui->stockbutton2,&QPushButton::clicked,this,[=](){
        ui->selectpage2->close();
        ui->selectpage2->show();
    });
    connect(ui->stockbutton3,&QPushButton::clicked,this,[=](){
        ui->selectpage3->close();
        ui->selectpage2->show();
    });
    connect(ui->stockbutton4,&QPushButton::clicked,this,[=](){
        ui->selectpage4->close();
        ui->selectpage2->show();
    });
    connect(ui->stockbutton5,&QPushButton::clicked,this,[=](){
        ui->selectpage5->close();
        ui->selectpage2->show();
    });
    connect(ui->rankbutton1,&QPushButton::clicked,this,[=](){
        ui->selectpage1->close();
        ui->selectpage3->show();
    });
    connect(ui->rankbutton2,&QPushButton::clicked,this,[=](){
        ui->selectpage2->close();
        ui->selectpage3->show();
    });
    connect(ui->rankbutton3,&QPushButton::clicked,this,[=](){
        ui->selectpage3->close();
        ui->selectpage3->show();
    });
    connect(ui->rankbutton4,&QPushButton::clicked,this,[=](){
        ui->selectpage4->close();
        ui->selectpage3->show();
    });
    connect(ui->rankbutton5,&QPushButton::clicked,this,[=](){
        ui->selectpage5->close();
        ui->selectpage3->show();
    });
    connect(ui->dealbutton1,&QPushButton::clicked,this,[=](){
        ui->selectpage1->close();
        ui->selectpage4->show();
    });
    connect(ui->dealbutton2,&QPushButton::clicked,this,[=](){
        ui->selectpage2->close();
        ui->selectpage4->show();
    });
    connect(ui->dealbutton3,&QPushButton::clicked,this,[=](){
        ui->selectpage3->close();
        ui->selectpage4->show();
    });
    connect(ui->dealbutton4,&QPushButton::clicked,this,[=](){
        ui->selectpage4->close();
        ui->selectpage4->show();
    });
    connect(ui->dealbutton5,&QPushButton::clicked,this,[=](){
        ui->selectpage5->close();
        ui->selectpage4->show();
    });
    connect(ui->communitybutton1,&QPushButton::clicked,this,[=](){
        ui->selectpage1->close();
        ui->selectpage5->show();
    });
    connect(ui->communitybutton2,&QPushButton::clicked,this,[=](){
        ui->selectpage2->close();
        ui->selectpage5->show();
    });
    connect(ui->communitybutton3,&QPushButton::clicked,this,[=](){
        ui->selectpage3->close();
        ui->selectpage5->show();
    });
    connect(ui->communitybutton4,&QPushButton::clicked,this,[=](){
        ui->selectpage4->close();
        ui->selectpage5->show();
    });
    connect(ui->communitybutton5,&QPushButton::clicked,this,[=](){
        ui->selectpage5->close();
        ui->selectpage5->show();
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

