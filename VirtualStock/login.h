#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "mainwindow.h"
#include "usermanage.h"
#include "enroll.h"
#include "ui_login.h"
#include <QKeyEvent>
#include <QPushButton>
#include <QMessageBox>
<<<<<<< HEAD
#include "global.h"
=======

extern UserManage usermanage;
>>>>>>> a9b89b36e241c5019cc123393d20395c9374dba1

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);

    ~Login();

<<<<<<< HEAD
    void keyPressEvent(QKeyEvent  *event) ;

    void loginErrorNotification(QString error);
=======
    int CheckUser(QString name, QString password);
    void keyPressEvent(QKeyEvent  *event) ;
>>>>>>> a9b89b36e241c5019cc123393d20395c9374dba1

private slots:
    void on_LoginButton_clicked();

    void on_RegisterButton_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
