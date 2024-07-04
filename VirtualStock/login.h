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

extern UserManage usermanage;

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);

    ~Login();

    int CheckUser(QString name, QString password);
    void keyPressEvent(QKeyEvent  *event) ;

private slots:
    void on_LoginButton_clicked();

    void on_RegisterButton_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
