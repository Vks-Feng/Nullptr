#include "personpage.h"
#include "ui_personpage.h"

Personpage::Personpage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Personpage)
{
    ui->setupUi(this);
    ui->userName->setText(Global::instance().getGlobalUserManage()->GetUser(0).GetName());
    //ui->trackedCount->setText(Global::instance().getGlobalUserManage()->GetUser(0).GetRanking().);
    //ui->successRate->setText(Global::instance().getGlobalUserManage()->GetUser(0).);
}

Personpage::~Personpage()
{
    delete ui;
}
