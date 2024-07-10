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
    ui->personalDescribeEdit->setText(Global::instance().getGlobalDataBase()->getIntroduction(Global::instance().getGlobalUserManage()->GetUser(0)->GetId()));
    ui->personalDescribeEdit->setDisabled(true);
    connect(ui->ChargeButton, &QPushButton::clicked, this, &Personpage::openChargePage);



    //设置右侧文本
    //当月资产计算
    int thisall=Global::instance().getGlobalDataBase()->getTotalvalue(Global::instance().getGlobalUserManage()->GetUser(0)->GetId());//本月总资产
    int lastvalue = 0;//lastvalue是盈利钱数
    int time=Global::instance().getGlobalDataBase()->getTime(Global::instance().getGlobalUserManage()->GetUser(0)->GetId());
    if(time==1){lastvalue=thisall-lastvalue;}
    else{
    std::vector<Record>load=Global::instance().getGlobalDataBase()->getUserRecord(Global::instance().getGlobalUserManage()->GetUser(0)->GetId());
    int number=load.size();
    QString thismonth;
    for(int i=0;i<number;i++){
        thismonth+=load[i].GetDate()[5];
        thismonth+=load[i].GetDate()[6];
        qDebug()<<thismonth;
        int thistime=QString(thismonth).toInt();
        if(thistime<time-1){qDebug()<<"continue";continue;}
        else if(thistime>time-1){qDebug()<<"end";break;}
        else{
            qDebug()<<"开始添加";
            if(load[i].GetTradeType()){
                lastvalue-=load[i].GetVolume();
            }
            else{
                lastvalue+=load[i].GetVolume();
            }
        }
    }
    }
    float lo=lastvalue/thisall;
    ui->profitRateMonthContent->setText(QString::number(lo));
    lo=(thisall-64800)/64800;
    ui->profitRateMonthContent->setDisabled(true);
    ui->phaseMonthContent->setText(QString::number(lastvalue));
    ui->phaseMonthContent->setDisabled(true);
    ui->balanceMonthContent->setText(QString::number(Global::instance().getGlobalUserManage()->GetUser(0)->GetBalance()));
    ui->balanceMonthContent->setDisabled(true);
    ui->profitRateTotalContent->setText(QString::number(lo));
    ui->profitRateTotalContent->setDisabled(true);
    ui->phaseTotalContent->setText(QString::number(thisall-64800));
    ui->phaseTotalContent->setDisabled(true);
    ui->balanceTotalContent->setText(QString::number(thisall));
    ui->balanceTotalContent->setDisabled(true);
}

void Personpage::openChargePage(){
    ChargePage* cg = new ChargePage;
    cg->show();
}

Personpage::~Personpage()
{
    delete ui;
}


void Personpage::on_changeintroduction_clicked()
{
    if(ui->changeintroduction->text()=="更改个性签名"){
    ui->personalDescribeEdit->setDisabled(false);
        temp=ui->personalDescribeEdit->toPlainText();
    ui->changeintroduction->setText("确认");
    }
    else{
        if(ui->personalDescribeEdit->toPlainText()==temp){
            QMessageBox msgBox;
            msgBox.setText("更改后的个性签名不能与原签名相同！");
            msgBox.exec();
            return;
        }
        else{
            ui->personalDescribeEdit->setDisabled(true);
            Global::instance().getGlobalDataBase()->setIntroduction(Global::instance().getGlobalUserManage()->GetUser(0)->GetId(),ui->personalDescribeEdit->toPlainText());
            ui->changeintroduction->setText("更改个性签名");
            QMessageBox msgBox;
            msgBox.setText("更改成功！");
            msgBox.exec();
            return;
        }
    }
}

