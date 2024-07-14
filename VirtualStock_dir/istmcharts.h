#ifndef ISTMCHARTS_H
#define ISTMCHARTS_H

#include <QWidget>
#include <QtCharts>
#include <QChartView>
#include <QSplineSeries>
#include <QRandomGenerator>//获取随机数用
#include "global.h"


namespace Ui {
class IstmCharts;
}

class IstmCharts : public QWidget
{
    Q_OBJECT

public:
    explicit IstmCharts(QWidget *parent = nullptr);
    void ShowRandomStock();//随机显示一支股票
    void ChangeStock(int company_id);
    //更改到指定公司的股票显示(0~7)
    ~IstmCharts();

private:
    Ui::IstmCharts *ui;
};

#endif // ISTMCHARTS_H
