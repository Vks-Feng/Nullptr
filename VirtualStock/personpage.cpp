#include "personpage.h"
#include "ui_personpage.h"

Personpage::Personpage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Personpage)
{
    ui->setupUi(this);
}

Personpage::~Personpage()
{
    delete ui;
}
