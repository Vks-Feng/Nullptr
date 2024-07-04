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

private slots:
    void on_BuyInButton_clicked();

    void on_SellOutButton_clicked();

    void on_TradingRecordButton_clicked();

    void on_PositionButton_clicked();

    void on_IncomeButton_clicked();

    void on_RecommendButton_clicked();

private:
    Ui::buyin *ui;
};

#endif // BUYIN_H
