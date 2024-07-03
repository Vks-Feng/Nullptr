#include "querywidget.h"
#include "ui_querywidget.h"
#include "backdb.h"

QueryWidget::QueryWidget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->GetQuery->setPlainText("select * from stock_data_monthly;");

    connect(ui->EnsureButton,SIGNAL(clicked(bool)),this,SLOT(PerformQuery()));
}

QueryWidget::PerformQuery()
{
    BackDB test;
    QString text=ui->GetQuery->toPlainText();
    qDebug()<<text<<Qt::endl;
    const char *query = text.toUtf8().constData();
    QString result=test.showQuery(query);
    qDebug()<<result<<Qt::endl;

    // Set the plain text
    ui->plainTextEdit->setPlainText(result);

    // Optionally, set the size of the QPlainTextEdit
    ui->plainTextEdit->resize(400, 300);

    // Set the QPlainTextEdit as the central widget of the main window
    this->setCentralWidget(ui->plainTextEdit);
}


QueryWidget::~QueryWidget()
{
    delete ui;
}

