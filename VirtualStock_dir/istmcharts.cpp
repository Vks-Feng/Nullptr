#include "istmcharts.h"
#include "ui_istmcharts.h"
#include "global.h"

IstmCharts::IstmCharts(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IstmCharts)
{
    std::cout<<"Hello , in istm "<<std::endl;
    ui->setupUi(this);
    this->setStyleSheet("background-color:white");
    ShowRandomStock();
}

void IstmCharts::ShowRandomStock()
{
    // 获取1到9之间的随机数
    int randomNumber = QRandomGenerator::global()->bounded(0, 7);
    ChangeStock(randomNumber);
}

void IstmCharts::ChangeStock(int company_id)
{
    qDebug()<<"Enter change stock";
        QStringList company_names = {
            "AAPL", "AMZN", "GOOGL", "IBM", "INTC",
            "JBLU", "META", "MSFT"
        };

        QString company_name;

        if (company_id >= 0 && company_id < company_names.size())
        {
            company_name = company_names[company_id];
        }
        else {
            company_name = "Unknown";
        }

        qDebug() << "Selected company:" << company_name;



//-------------------------Get the data of the IBM from database


//        BackDB test = *Global::instance().getGlobalDataBase();

        BackDB test;

        QString queryStr = QString("SELECT month, value FROM lstm_predict \
                                    WHERE company_name = '%1' \
                                    ORDER BY month;")
                               .arg(company_name);

        MYSQL_RES* result=test.query(queryStr);

            qDebug()<<"Finish the query sentence";

        //如果返回行数为空，也就是说没有查询到有效值的话
        //那么将一个label放到原本图表的位置上

        if (mysql_num_rows(result) == 0) { //此处绝对不能用==NULL进行判定

            std::cerr << "Failed to get the result set in Spline" << std::endl;

            QLabel* label=new QLabel;

            // 设置 QLabel 的文本内容
            label->setText("Please input the correct company_name!!!");

            // 设置 QLabel 的样式
            label->setStyleSheet("font-size: 18px; color: red;");

            ui->horizontalLayout->addWidget(label);

            this->setLayout(ui->horizontalLayout);

            return ;

        }


        MYSQL_ROW row;
        std::vector<double> data;

        while ((row = mysql_fetch_row(result))) {

            QString qStr_0(row[0]);
            QString qStr_1(row[1]);

            bool ok;
//            int month= qStr_0.toInt(&ok);
            double value = qStr_1.toDouble(&ok);

//            std::cout<<ok<<std::endl;
            if (!ok) {
                qDebug() << "Cannot Converted number:" << qStr_0 <<" OR "<<qStr_1;
            }
            else
            {
//                std::cout<<value<<std::endl;
                data.push_back(value);
//                std::cout<<data.size()<<std::endl;
            }
        }

        auto chart = new QChart;
        auto lineseries = new QLineSeries;
        QStringList categories;
        //lineseries->setName("总和");

        int time=Global:: instance().getGlobalDataBase()->getTime(Global::instance().getGlobalUserManage()->GetUser(0)->GetId());

        if(time>=1&&time<=6)
        {
            for(int i=0;i<6;i++)
            {
                lineseries->append(QPoint(i, data[i]));
            }
            lineseries->setName(company_name+ "-" +
                                "Istm 1~6月 预测价格");

            for(int i=1;i<=6;i++){
                categories << QString::number(i);
            }
        }
        else
        {
            for(int i=6;i<12;i++)
            {
                lineseries->append(QPoint(i-6, data[i]));//QPoint固定从0开始
            }
            lineseries->setName(company_name+ "-" +
                                "Istm 7~12月 预测价格");


            for(int i=7;i<=12;i++)
            {
                categories << QString::number(i);
            }
        }



        chart->addSeries(lineseries);

        auto axisX = new QBarCategoryAxis;
        axisX->append(categories);

        chart->addAxis(axisX, Qt::AlignBottom);
        lineseries->attachAxis(axisX);


        auto axisY = new QValueAxis;
        chart->addAxis(axisY, Qt::AlignLeft);
        lineseries->attachAxis(axisY);

        axisY->setLabelFormat("%.2f"); //标签格式
        axisY->setTickCount(1);
        axisY->setMinorTickCount(2);

        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);


        QColor selectedColor;
        std::vector<QColor> colors;

        // 随机给出颜色
        colors = { QColor(Qt::red), QColor(Qt::green), QColor(Qt::blue), QColor(255,165,0) };

        // Select a random color using QRandomGenerator
        int randomIndex = QRandomGenerator::global()->bounded(static_cast<int>(colors.size()));
        selectedColor = colors[randomIndex];

        QPen pen(selectedColor);
        pen.setWidth(3);
        lineseries->setPen(pen);

        QChartView *chartView = new QChartView(this);
        chartView->setChart(chart);

//        chartView->resize(QSize(500,300));              //重新设置chartView的大小

        chartView->setRenderHints(QPainter::Antialiasing);//消除边缘，看起来平滑一些

        // 清空当前容器中的所有小部件
        QLayoutItem *child;
        while ((child = ui->horizontalLayout->takeAt(0)) != nullptr) {
            delete child->widget();
            delete child;
        }

        ui->horizontalLayout->addWidget(chartView);    //把chartView放到水平布局中（在ui中拖一个水平布局）
        this->setLayout(ui->horizontalLayout);

        // this->resize(700,500);

    QObject::connect(lineseries, &QSplineSeries::hovered, [=](const QPointF &point, bool state)mutable
    {

        QList<int> yList;
        for (int i=0; i<lineseries->points().size(); ++i)
        {
            yList.append(qRound(lineseries->points().at(i).y()));
        }
        int y = qRound(point.y());
        if (state)
        {
            for (int i=0; i<5; ++i)
            {
                if (yList.contains(y + i))
                {
                    QToolTip::showText(QCursor::pos(), QString("%1").arg(y + i));
                    break;
                }
                if (yList.contains(y - i))
                {
                    QToolTip::showText(QCursor::pos(), QString("%1").arg(y - i));
                    break;
                }
            }
        }
    });

        qDebug()<<"Drop out of the istmcharts";
}



IstmCharts::~IstmCharts()
{
    delete ui;
}
