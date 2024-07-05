#include "enroll.h"
#include "ui_enroll.h"
#include "login.h"

enroll::enroll(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::enroll)
{
    ui->setupUi(this);

}

enroll::~enroll()
{
    delete ui;
}

void enroll::on_LoginButton_clicked()
{
    Login *loh =new Login();
    this->close();
    loh->show();
}

