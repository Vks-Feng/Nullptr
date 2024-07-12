#ifndef CHARTSPLINE_H
#define CHARTSPLINE_H

#include <QWidget>
#include <QtCharts>
#include <QChartView>
#include <QSplineSeries>
#include <QRandomGenerator>//获取随机数用
#include "global.h"


namespace Ui {
class ChartSpline;
}

class ChartSpline : public QWidget
{
    Q_OBJECT

public:
    explicit ChartSpline(QWidget *parent = nullptr);
    ~ChartSpline();

public slots:
    void ShowRandomStock();//随机显示一支股票
    void ChangeStock(int company_id);//更改到指定公司的股票显示(0~7)
//    QString CompanyIntroduction(int company_id);//返回对应公司的简介(0~7)

private:
    Ui::ChartSpline *ui;
};

#endif // CHARTSPLINE_H
