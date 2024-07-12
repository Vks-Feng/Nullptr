#include "chartspline.h"
#include "ui_chartspline.h"


//#include <Qtime>
#include <vector>

const int YEARS=25;

ChartSpline::ChartSpline(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChartSpline)
{
    std::cout<<"Hello , in spline "<<std::endl;
    ui->setupUi(this);
    this->setStyleSheet("background-color:white");
    ShowRandomStock();
}

ChartSpline::~ChartSpline()
{
        delete ui;
}

void ChartSpline::ShowRandomStock()
{
        // 获取1到9之间的随机数
        int randomNumber = QRandomGenerator::global()->bounded(0, 8);
        ChangeStock(randomNumber);
}

void ChartSpline::ChangeStock(int company_id)
{
        QStringList company_names = {
            "AAPL", "AMZN", "GOOGL", "IBM", "INTC",
            "JBLU", "META", "MSFT", "TSLA"
        };

        QString company_name;

        if (company_id >= 0 && company_id < company_names.size()) {
            company_name = company_names[company_id];
        } else {
            company_name = "Unknown";
        }

        qDebug() << "Selected company:" << company_name;

        std::vector<double> data;

//-------------------------Get the data of the IBM from database


        BackDB test = *Global::instance().getGlobalDataBase();

        QString queryStr = QString("SELECT YEAR(timestamp) AS year,\
                                    AVG((high + low) / 2) AS mean_value FROM stock_data_monthly \
                                    WHERE CompanyName = '%1'AND MONTH(timestamp) = 1 \
                                    GROUP BY YEAR(timestamp) ORDER BY year;")
                               .arg(company_name);

        MYSQL_RES* result=test.query(queryStr);

        //如果返回行数为空，也就是说没有查询到有效值的话
        //那么将一个label放到原本图表的位置上

        if (mysql_num_rows(result) == 0) { //此处绝对不能用==NULL进行判定
            std::cout << "Failed to get the result set in Spline" << std::endl;

            QLabel* label=new QLabel;

            // 设置 QLabel 的文本内容
            label->setText("Please input the correct company_name!!!");

            // 设置 QLabel 的样式
            label->setStyleSheet("font-size: 18px; color: red;");

            ui->horizontalLayout->addWidget(label);

            this->setLayout(ui->horizontalLayout);
//            this->resize(700,500);

            return ;

        }


        MYSQL_ROW row;

        int start_year;//从哪一年开始
        int years_num=0;// 标记是否为第二行，也就是最早年的开始

        while ((row = mysql_fetch_row(result))) {

            QString qStr(row[1]);
            bool ok;
            double number = qStr.toDouble(&ok);

//            std::cout<<ok<<std::endl;
            if (!ok) {
                qDebug() << "Cannot Converted number:" << number;
            }
            else
            {
//                std::cout<<number<<std::endl;
                data.push_back(number);
//                std::cout<<data.size()<<std::endl;
                years_num++;
            }

            if(years_num==1)
            {
                QString qStr(row[0]);
                start_year = qStr.toInt(&ok);
            }//将初始年份设置好

//            std::cout << row[1]<<std::endl;
            //因为第一个数值是年份，dirge数值才是平均值
            //大体结果 2010 145.5050000000
        }

        years_num-=2; //因为是从2023年开始，所以往回退两年



//-------------------------------

//        connect(ui->QuitSpline,SIGNAL(clicked(bool)),this,SLOT(close()));


        auto lineseries = new QLineSeries;
        //lineseries->setName("总和");

        for(int i=0;i<years_num;i++)
        {
            lineseries->append(QPoint(i, data[i]));
        }

        auto chart = new QChart;

        chart->addSeries(lineseries);
        chart->setTitle(company_name + " 公司: " + QString::number(start_year) + "-" +
               QString::number(start_year + years_num-1) + "年股票单价行情");


        QStringList categories;
        for(int i=0;i<years_num;i++){
            categories << QString::number(start_year+i-2000);
        }

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

        // QPen pen(QColor(255, 165, 0));  // 使用橙色
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

//        this->resize(700,500);
}

//QString ChartSpline::CompanyIntroduction(int company_id)
//{

//}
