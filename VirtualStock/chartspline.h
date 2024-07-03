#ifndef CHARTSPLINE_H
#define CHARTSPLINE_H

#include <QWidget>
#include <QtCharts>
#include <QChartView>
#include <QSplineSeries>


namespace Ui {
class ChartSpline;
}

class ChartSpline : public QWidget
{
    Q_OBJECT

public:
    explicit ChartSpline(QWidget *parent = nullptr);
    ~ChartSpline();

private:
    Ui::ChartSpline *ui;
};

#endif // CHARTSPLINE_H
