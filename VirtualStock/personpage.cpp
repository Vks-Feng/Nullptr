#include "personpage.h"
#include "ui_personpage.h"

Personpage::Personpage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Personpage)
{
    ui->setupUi(this);
<<<<<<< HEAD
    ui->userName->setText(Global::instance().getGlobalUserManage()->GetUser(0)->GetName());
    //ui->trackedCount->setText(Global::instance().getGlobalUserManage()->GetUser(0).GetRanking().);
    //ui->successRate->setText(Global::instance().getGlobalUserManage()->GetUser(0).);
=======
>>>>>>> a9b89b36e241c5019cc123393d20395c9374dba1
}

Personpage::~Personpage()
{
    delete ui;
}
