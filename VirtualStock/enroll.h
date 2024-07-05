#ifndef ENROLL_H
#define ENROLL_H

#include <QWidget>
#include <QPushButton>
#include "global.h"
#include "login.h"

namespace Ui {
class enroll;
}

class enroll : public QWidget
{
    Q_OBJECT

public:
    explicit enroll(QWidget *parent = nullptr);

    void enrollNotification(QString error);
    ~enroll();
    void on_LoginButton_clicked();

private:
    Ui::enroll *ui;
};

#endif // ENROLL_H