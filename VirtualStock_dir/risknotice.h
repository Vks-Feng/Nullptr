#ifndef RISKNOTICE_H
#define RISKNOTICE_H

#include <QDialog>

namespace Ui {
class RiskNotice;
}

class RiskNotice : public QDialog
{
    Q_OBJECT

public:
    explicit RiskNotice(QWidget *parent = nullptr);
    ~RiskNotice();

private:
    Ui::RiskNotice *ui;
};

#endif // RISKNOTICE_H
