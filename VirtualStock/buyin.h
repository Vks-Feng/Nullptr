#ifndef BUYIN_H
#define BUYIN_H

#include <QWidget>

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

private slots:
    void on_BuyInButton_clicked();

    void on_SellOutButton_clicked();

    void on_TradingRecordButton_clicked();

    void on_PositionButton_clicked();

    void on_IncomeButton_clicked();

    void on_RecommendButton_clicked();

    void on_returnbutton_clicked();

private:

};

#endif // BUYIN_H
