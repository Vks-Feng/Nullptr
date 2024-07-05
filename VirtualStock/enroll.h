#ifndef ENROLL_H
#define ENROLL_H

#include <QWidget>
#include <QPushButton>
<<<<<<< HEAD
#include "global.h"
#include "login.h"

=======
>>>>>>> a9b89b36e241c5019cc123393d20395c9374dba1
namespace Ui {
class enroll;
}

class enroll : public QWidget
{
    Q_OBJECT

public:
    explicit enroll(QWidget *parent = nullptr);
<<<<<<< HEAD

    void enrollNotification(QString error);

=======
>>>>>>> a9b89b36e241c5019cc123393d20395c9374dba1
    ~enroll();

private slots:
    void on_LoginButton_clicked();

private:
    Ui::enroll *ui;
};

#endif // ENROLL_H
