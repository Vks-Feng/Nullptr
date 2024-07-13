#ifndef DIALOG_H
#define DIALOG_H
#include <QDialog>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>
#include <QPushButton>
#include "global.h"
class dialog: public QDialog
{Q_OBJECT
public:
    dialog(QWidget *parent = nullptr) : QDialog(parent) {
        auto *layout = new QVBoxLayout(this);
        int userID = Global::instance().getGlobalUserManage()->GetUser(0)->GetId();

        QTableWidget *tableWidget = new QTableWidget(9, 8);
        QStringList headerLabels;
        headerLabels << "公司股票"<< "上月股价"<<"本月股价"<< "持有量"<<"上月总股价"<<"本月总股价"<<"盈亏"<<"盈利率";
        tableWidget->setHorizontalHeaderLabels(headerLabels);
        Portfolio* userHoldings = &Global::instance().getGlobalDataBase()->getUserPortfolio(userID);
        QTableWidgetItem* iHolding;
        QTableWidgetItem* singlevalue;
        QTableWidgetItem* lastsinglevalue;
        QTableWidgetItem* iTotalValue;
        QTableWidgetItem* lastiTotalValue;
        QTableWidgetItem* Bep;
        QTableWidgetItem* Rate;
        long summaryHolding = 0;
        long summaryValue = 0;
        long summarylastValue = 0;

        QStringList company_names = {
                                     "AAPL", "AMZN", "GOOGL", "IBM", "INTC",
                                     "JBLU", "META", "MSFT", "total"};
        for(int i = 0; i < 8; i++){
            int year = Global::instance().getYear();
            int month = Global::instance().getGlobalDataBase()->getTime(userID);
            QTableWidgetItem* iStockID= new QTableWidgetItem(QString(company_names[i]));
            int holdings = userHoldings->getHoldings(i+1);
            int singleValue = Global::instance().getGlobalDataBase()->getStockInfo(i+1, year, month)[0];
            int totalValue = holdings * singleValue;
            int lastsingleValue = Global::instance().getGlobalDataBase()->getStockInfo(i+1, year, month-1)[0];
            int lastvalue = holdings * lastsingleValue;
            int bep=totalValue-lastvalue;
            int rate=100*(singleValue-lastsingleValue)/lastsingleValue;
            singlevalue= new QTableWidgetItem(QString::number(singleValue));
            lastsinglevalue= new QTableWidgetItem(QString::number(lastsingleValue));
            iHolding = new QTableWidgetItem(QString::number(userHoldings->getHoldings(i+1)));
            iTotalValue = new QTableWidgetItem(QString::number(totalValue));
            lastiTotalValue = new QTableWidgetItem(QString::number(lastvalue));
            Bep = new QTableWidgetItem(QString::number(bep));
            Rate = new QTableWidgetItem(QString::number(rate)+"%");
            tableWidget->setItem(i,0,iStockID);
            tableWidget->setItem(i,1,lastsinglevalue);
            tableWidget->setItem(i,2,singlevalue);
            tableWidget->setItem(i, 3, iHolding);
            tableWidget->setItem(i, 4, lastiTotalValue);
            tableWidget->setItem(i, 5, iTotalValue);
            tableWidget->setItem(i, 6, Bep);
            tableWidget->setItem(i, 7, Rate);
            summaryHolding += holdings;
            summaryValue += totalValue;
            summarylastValue+=lastvalue;
        }
        QTableWidgetItem* iStockID= new QTableWidgetItem(QString(company_names[8]));
        int totalbep= summaryValue-summarylastValue;
        double totalrate;
        if(summarylastValue==0){

            totalrate=0;
        }
        else{
            totalrate= 100*(summaryValue-summarylastValue)/summarylastValue;
        }
        iHolding = new QTableWidgetItem(QString::number(summaryHolding));
        iTotalValue = new QTableWidgetItem(QString::number(summaryValue));
        lastiTotalValue = new QTableWidgetItem(QString::number(summarylastValue));
        Bep = new QTableWidgetItem(QString::number(totalbep));
        Rate =new QTableWidgetItem(QString::number(totalrate)+"%");
        tableWidget->setItem(8,0,iStockID);
        tableWidget->setItem(8, 3, iHolding);
        tableWidget->setItem(8, 5, iTotalValue);
        tableWidget->setItem(8, 4, lastiTotalValue);
        tableWidget->setItem(8, 6, Bep);
        tableWidget->setItem(8, 7, Rate);

        layout->addWidget(tableWidget);

        auto *button = new QPushButton("Close", this);
        connect(button, &QPushButton::clicked, this, &QDialog::accept);
        layout->addWidget(button);

        setLayout(layout);
        QSize size = tableWidget->sizeHint();
        size.setHeight(size.height() + button->sizeHint().height() + layout->spacing());
        size = size.expandedTo(QSize(600, 400));
        tableWidget->resizeColumnsToContents();
        resize(size);  }

    QTableWidget *tableWidget;


};

// 在某个函数或槽中创建并显示对话框

#endif // DIALOG_H
