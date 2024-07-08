#include "personpage.h"
#include "ui_personpage.h"

Personpage::Personpage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Personpage)
{
    ui->setupUi(this);
    Global::instance().getGlobalUserManage()->updateUser(0);
    ui->userName->setText(Global::instance().getGlobalUserManage()->GetUser(0)->GetName());
    ui->userName->setDisabled(true);
    ui->trackedCount->setText(QString::number(Global::instance().getGlobalUserManage()->GetUser(0)->GetRanking()));
    ui->trackedCount->setDisabled(true);
    ui->successRate->setText(QString::number(Global::instance().getGlobalUserManage()->GetUser(0)->GetBalance()));
    ui->successRate->setDisabled(true);
    connect(ui->ChargeButton, &QPushButton::clicked, this, &Personpage::openChargePage);
}

void Personpage::openChargePage(){
    ChargePage* cg = new ChargePage;
    cg->show();
}

Personpage::~Personpage()
{
    delete ui;
}
