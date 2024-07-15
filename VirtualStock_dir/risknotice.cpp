#include "risknotice.h"
#include "ui_risknotice.h"

RiskNotice::RiskNotice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RiskNotice)
{
    ui->setupUi(this);
    connect(ui->confirmButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(ui->cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

RiskNotice::~RiskNotice()
{
    delete ui;
}
