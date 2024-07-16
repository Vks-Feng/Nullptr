#include "personpage.h"
#include "ui_personpage.h"

Personpage::Personpage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Personpage)
{
    ui->setupUi(this);

    //标签插图，自适应大小
    ui->userPicLabel->setScaledContents(true);
    ui->active_Label->setScaledContents(true);
    ui->total_Label->setScaledContents(true);
    ui->month_Label->setScaledContents(true);
    ui->monthProfit_Label->setScaledContents(true);
    ui->totalRate_Label->setScaledContents(true);
    ui->totalProfit_Label->setScaledContents(true);

    Global::instance().getGlobalUserManage()->updateUser(0);
    ui->userName->setText(Global::instance().getGlobalUserManage()->GetUser(0)->GetName());
    ui->userName->setDisabled(true);
    ui->trackedCount->setText(QString::number(Global::instance().getGlobalUserManage()->GetUser(0)->GetRanking()));
    ui->trackedCount->setDisabled(true);
    ui->personalDescribeEdit->setText(Global::instance().getGlobalDataBase()->getIntroduction(Global::instance().getGlobalUserManage()->GetUser(0)->GetId()));
    ui->personalDescribeEdit->setDisabled(true);
    // connect(ui->ChargeButton, &QPushButton::clicked, this, &Personpage::openChargePage);



    //设置右侧文本
    //当月资产计算
    int thisall=Global::instance().getGlobalDataBase()->getTotalvalue(Global::instance().getGlobalUserManage()->GetUser(0)->GetId());//本月总资产
    int lastvalue=lastcurrency();
    int lo=lastvalue*10000/thisall;
    ui->profitRateMonthContent->setText(QString::number(lo)+"%%");
    lo=(thisall-64800)*10000/64800;
    ui->profitRateMonthContent->setDisabled(true);
    ui->phaseMonthContent->setText(QString::number(lastvalue));
    ui->phaseMonthContent->setDisabled(true);
    ui->balanceMonthContent->setText(QString::number(Global::instance().getGlobalUserManage()->GetUser(0)->GetBalance()));
    ui->balanceMonthContent->setDisabled(true);
    ui->profitRateTotalContent->setText(QString::number(lo)+"%%");
    ui->profitRateTotalContent->setDisabled(true);
    ui->phaseTotalContent->setText(QString::number(thisall-64800));
    ui->phaseTotalContent->setDisabled(true);
    ui->balanceTotalContent->setText(QString::number(thisall));
    ui->balanceTotalContent->setDisabled(true);
    this->setAttribute(Qt::WA_DeleteOnClose, true);
    this->setWindowTitle("个人主页");
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
float Personpage::lastcurrency(){
    int thisall=Global::instance().getGlobalDataBase()->getTotalvalue(Global::instance().getGlobalUserManage()->GetUser(0)->GetId());//本月总资产
    int lastvalue = 0;//lastvalue是盈利钱数
    int time=Global::instance().getGlobalDataBase()->getTime(Global::instance().getGlobalUserManage()->GetUser(0)->GetId());
    if(time==1){lastvalue=0;}
    else{
        std::vector<Record>load=Global::instance().getGlobalDataBase()->getUserRecord(Global::instance().getGlobalUserManage()->GetUser(0)->GetId());
        int number=load.size();

        //获取所有当月股票的交易记录
        int havestock[9]={0};

        for(int i=0;i<number;i++){
            QString thismonth;
            thismonth+=load[i].GetDate()[5];
            thismonth+=load[i].GetDate()[6];
            int thistime=QString(thismonth).toInt();
            if(thistime<time){continue;}
            else if(thistime>time){break;}
            else{
                qDebug()<<thistime<<" ";
                if(load[i].GetTradeType()){
                    havestock[load[i].GetCompanyId()]+=load[i].GetVolume();
                    if(havestock[load[i].GetCompanyId()]==-1){
                        havestock[load[i].GetCompanyId()]=0;
                    }
                }
                else{
                    havestock[load[i].GetCompanyId()]-=load[i].GetVolume();
                    if(havestock[load[i].GetCompanyId()]==-1){
                        havestock[load[i].GetCompanyId()]=0;
                    }}
            }
            //thismonth="";
            //thismonth.clear();
        }


        //
        int stockcurrency[9];//所有股票价格
        //
        for(int i=1;i<9;i++){
            qDebug()<<havestock[i];
            std::vector<long>& stockInfo1 = Global::instance().getGlobalDataBase()->getStockInfo(i, 2023, time-1);
            long stockPrice1 = stockInfo1[0]; // 获取股票上个月价格
            int number1=Global::instance().getGlobalDataBase()->getUserVolume(Global::instance().getGlobalUserManage()->GetUser(0)->GetId(),i);
            if(number1==-1){number1=0;}
            std::vector<long>& stockInfo2 = Global::instance().getGlobalDataBase()->getStockInfo(i, 2023, time);
            long stockPrice2 = stockInfo2[0]; // 获取股票这个月价格

            stockcurrency[i]=(stockPrice2-stockPrice1)*(number1-havestock[i]);
            //number1-havestock[i]是上月末股票持有量
            //stockcurrency[i]就是该只股票带来的收益

            lastvalue+=stockcurrency[i];//上月总收益
            return lastvalue;
        }}

    return lastvalue;
}

