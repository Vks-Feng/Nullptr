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
    void keyPressEvent(QKeyEvent  *event) ;
    ~enroll();



private slots:
    void on_registerButton_clicked();

private:
    Ui::enroll *ui;
};

#endif // ENROLL_H
