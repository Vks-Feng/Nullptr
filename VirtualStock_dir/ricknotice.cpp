#include "ricknotice.h"
#include "ui_ricknotice.h"

RickNotice::RickNotice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RickNotice)
{
    ui->setupUi(this);
}

RickNotice::~RickNotice()
{
    delete ui;
}
