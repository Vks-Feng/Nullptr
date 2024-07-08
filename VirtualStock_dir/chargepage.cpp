#include "chargepage.h"
#include "ui_chargepage.h"

ChargePage::ChargePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChargePage)
{
    ui->setupUi(this);
    ui->ChargeInput->setValidator(new QIntValidator(0, 9999, ui->ChargeInput));
    connect(ui->ChargeConfirm, &QPushButton::clicked, this, &ChargePage::confirmCharge);
}

void ChargePage::chargeNotification(QString msg){
    QMessageBox msgBox;
    msgBox.setText(msg);
    msgBox.exec();
}

void ChargePage::confirmCharge(){
    if(ui->ChargeInput->text().isEmpty()){
        chargeNotification("充值金额为空，白送的钱都不要٩(๑`^´๑)۶");
    } else {
        int chargeValue = ui->ChargeInput->text().toInt();
        int id = Global::instance().getGlobalUserManage()->GetUser(0)->GetId();
        Global::instance().getGlobalDataBase()->inclineBalance(id, chargeValue);
        Global::instance().getGlobalUserManage()->updateUser(0);
        chargeNotification("充值成功");
    }
}

ChargePage::~ChargePage()
{
    delete ui;
}
