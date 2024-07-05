#ifndef BUYIN_H
#define BUYIN_H

#include <QWidget>
#include "global.h"
#include<QString>

    namespace Ui {
    class buyin;
}

class buyin : public QWidget
{
    Q_OBJECT

public:
    explicit buyin(QWidget *parent = nullptr);
    ~buyin();
    Ui::buyin *ui;
    void resetvalue();

    void resetvalue_2();
private slots:
    void on_BuyInButton_clicked();

    void on_SellOutButton_clicked();

    void on_TradingRecordButton_clicked();

    void on_PositionButton_clicked();

    void on_IncomeButton_clicked();

    void on_RecommendButton_clicked();

    void on_returnbutton_clicked();

    void on_StockCodeBox_2_currentIndexChanged(int index);

    void on_StockCodeBox_currentIndexChanged(int index);

    void on_QuantityLine_textChanged(const QString &arg1);

    void on_BuyResetButton_clicked();

    void on_BuyComfirmButton_clicked();

    void on_QuantityLine_2_textChanged(const QString &arg1);

    void on_SellResetButton_clicked();

    void on_SellComfirmButton_clicked();

private:
    int id;//股票编号
    int maxnum;//最大购买数量同卖出
    int buynum;//用户输入购买数量同卖出
    double value;//对应股票价格
    bool r1,r2;//用来确认用户是否填完所需内容
    Stock *stock;//对应的股票
};

#endif // BUYIN_H
