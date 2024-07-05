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
#include "global.h"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);

    ~Login();

    void keyPressEvent(QKeyEvent  *event) ;

    void loginErrorNotification(QString error);

private slots:
    void on_LoginButton_clicked();

    void on_RegisterButton_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
