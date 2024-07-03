#include "login.h"
#include "mainwindow.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
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

