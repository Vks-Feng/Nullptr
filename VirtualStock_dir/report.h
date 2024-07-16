#ifndef REPORT_H
#define REPORT_H

#include <QDialog>
#include "global.h"

namespace Ui {
class Report;
}

class Report : public QDialog
{
    Q_OBJECT

public:
    explicit Report(QWidget *parent = nullptr);
    ~Report();

private:
    Ui::Report *ui;
};

#endif // REPORT_H
