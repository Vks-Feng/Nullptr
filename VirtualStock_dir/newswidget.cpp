#include "newswidget.h"
#include "ui_newswidget.h"

NewsWidget::NewsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NewsWidget)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);

}

NewsWidget::~NewsWidget()
{
    delete ui;
}


