#ifndef BUYIN_H
#define BUYIN_H

#include <QWidget>
#include "global.h"
#include<QString>
#include <QMessageBox>

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
    void initBuyInSellOut();

    void buyinNotification(QString msg);

private slots:
    void on_BuyInButton_clicked();

    void on_SellOutButton_clicked();

    void on_TradingRecordButton_clicked();

    void on_PositionButton_clicked();

    void on_IncomeButton_clicked();

    void on_RecommendButton_clicked();

    void on_returnbutton_clicked();

    void on_QuantityLine_textChanged(const QString &arg1);

    void on_BuyResetButton_clicked();

    void on_BuyComfirmButton_clicked();

    void on_QuantityLine_2_textChanged(const QString &arg1);

    void on_SellResetButton_clicked();

    void on_SellComfirmButton_clicked();

    void on_BuyInStockCodeBox_currentIndexChanged(int index);

    void on_SellOutStockCodeBox_currentIndexChanged(int index);

private:

};

#endif // BUYIN_H
