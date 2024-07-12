#ifndef PERSONPAGE_H
#define PERSONPAGE_H

#include <QWidget>
#include "global.h"
#include "chargepage.h"
#include "backdb.h"
#include <QString>
#include <vector>
#include "record.h"
#include<qdebug.h>
namespace Ui {
class Personpage;
}

class Personpage : public QWidget
{
    Q_OBJECT

public:
    explicit Personpage(QWidget *parent = nullptr);

    void openChargePage();
    float lastcurrency();

    ~Personpage();

private slots:

    void on_changeintroduction_clicked();

private:
    Ui::Personpage *ui;
    QString temp;
};

#endif // PERSONPAGE_H
