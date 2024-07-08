#ifndef CHARGEPAGE_H
#define CHARGEPAGE_H

#include <QWidget>
#include <QString>
#include <QMessageBox>
#include "global.h"
#include <QIntValidator>

namespace Ui {
class ChargePage;
}

class ChargePage : public QWidget
{
    Q_OBJECT

public:
    explicit ChargePage(QWidget *parent = nullptr);

    void confirmCharge();

    void chargeNotification(QString msg);

    ~ChargePage();

private:
    Ui::ChargePage *ui;
};

#endif // CHARGEPAGE_H
