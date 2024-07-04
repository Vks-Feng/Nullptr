#include "login.h"
#include "mainwindow.h"
#include "enroll.h"
#include "ui_login.h"
#include <QKeyEvent>
#include <QPushButton>
#include <QMessageBox>
Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
    connect(ui->DetailButton,&QPushButton::clicked,[=](){
        QMessageBox::information(this,"详情","不知道写啥");
    });
}

Login::~Login()
{
    delete ui;
}

void Login::on_LoginButton_clicked()
{
    bool Loginsuccess = (ui->UserNameInput->text() == "vks") && (ui->UserPasswordInput->text() == "123");
    if(Loginsuccess) {
        MainWindow* mainwindow = new MainWindow();
        mainwindow->show();
        this->close();
    } else if(ui->UserPasswordInput->text() != "123") {

    }
}
void Login::keyPressEvent(QKeyEvent  *event)
{
    switch(event->key()){
    case Qt::Key_Return:
        on_LoginButton_clicked();
        break;
    case Qt::Key_Enter:
        on_LoginButton_clicked();
        break;
    default:
        break;
    }
}


void Login::on_RegisterButton_clicked()
{
    enroll* en =new enroll();
    this->close();
    en->show();
}

