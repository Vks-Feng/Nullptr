#include "chartspline.h"
#include "ui_chartspline.h"
#include "backdb.h"

#include <Qtime>
#include <QVector>

const int YEARS=25;

ChartSpline::ChartSpline(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChartSpline)
{
        std::cout<<"Hello , in spline "<<std::endl;
        ui->setupUi(this);
        this->setStyleSheet("background-color:white");
        setWindowTitle("当前公司股票近25年起伏情况");

        QVector<double> data;

//-------------------------Get the data of the IBM from database


        BackDB test;
        MYSQL_RES* result=test.query("SELECT YEAR(timestamp) AS year,\
                                    AVG((high + low) / 2) AS mean_value FROM stock_data_monthly \
                                    WHERE CompanyName = 'IBM'AND MONTH(timestamp) = 12 \
                                    GROUP BY YEAR(timestamp) ORDER BY year;");

        std::cout<<"Back in Spline"<<std::endl;

        if (result == nullptr) {
            std::cout << "Failed to get the result set in Spline" << std::endl;
        }
        else {

            // Process the result set if needed
            int num_fields = mysql_num_fields(result);
            MYSQL_ROW row;

            while ((row = mysql_fetch_row(result))) {

                QString qStr(row[1]);
                bool ok;
                double number = qStr.toDouble(&ok);

                std::cout<<ok<<std::endl;
                if (!ok) {
                    qDebug() << "Cannot Converted number:" << number;
                }
                else
                {
                    std::cout<<number<<std::endl;
                    data.append(number);
                    std::cout<<data.size()<<std::endl;
                }

                std::cout << row[1]<<std::endl;
                }

            }


//-------------------------------

        connect(ui->QuitSpline,SIGNAL(clicked(bool)),this,SLOT(close()));


        auto lineseries = new QLineSeries;
        //lineseries->setName("总和");

        for(int i=0;i<YEARS;i++)
        {
            lineseries->append(QPoint(i, data[i]));
        }

        auto chart = new QChart;

        chart->addSeries(lineseries);
        chart->setTitle("IBM国际商用机器公司1999-2024年股票单价行情");

        QStringList categories;
        for(int i=0;i<YEARS;i++){
            categories << QString::number(1999+i);
        }

            auto axisX = new QBarCategoryAxis;
        axisX->append(categories);

        chart->addAxis(axisX, Qt::AlignBottom);
        lineseries->attachAxis(axisX);

        axisX->setRange(QString("六天前"), QString("今天"));


        auto axisY = new QValueAxis;
        chart->addAxis(axisY, Qt::AlignLeft);
        lineseries->attachAxis(axisY);

        axisY->setLabelFormat("%.2f"); //标签格式
        axisY->setTickCount(1);
        axisY->setMinorTickCount(2);

        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);

        QPen pen(QColor(255, 165, 0));  // 使用橙色
        pen.setWidth(3);
        lineseries->setPen(pen);

        QChartView *chartView = new QChartView(this);
        chartView->setChart(chart);
        chartView->resize(QSize(500,300));              //重新设置chartView的大小
        chartView->setRenderHints(QPainter::Antialiasing);//消除边缘，看起来平滑一些
        ui->horizontalLayout->addWidget(chartView);    //把chartView放到水平布局中（在ui中拖一个水平布局）
        this->setLayout(ui->horizontalLayout);
        this->resize(700,500);
}

ChartSpline::~ChartSpline()
{
    delete ui;
}
