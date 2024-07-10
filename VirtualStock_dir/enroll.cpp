#include "enroll.h"
#include "ui_enroll.h"
#include "login.h"

enroll::enroll(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::enroll)
{
    ui->setupUi(this);

}

enroll::~enroll()
{
    delete ui;
}

void enroll::enrollNotification(QString error){
    QMessageBox msgBox;
    msgBox.setText(error);
    msgBox.exec();
}

//实际上是注册键
//void enroll::on_LoginButton_clicked()
//{
//    qDebug() << "called" ;
//    if (ui->UserNameInput->text().isEmpty() || ui->UserPasswordInput->text().isEmpty()) {
//        enrollNotification("用户名和密码不能为空");
//    } else {
//        if(Global::instance().getGlobalUserManage()->Create(ui->UserNameInput->text(), ui->UserPasswordInput->text())){
//            enrollNotification("注册成功，请点击确认返回登录");
//            Login* l = new Login();
//            l->show();
//            this->close();
//        } else {
//            enrollNotification("用户名已存在，请更换用户名");
//        }
//    }
//}


void enroll::on_registerButton_clicked()
{
    qDebug() << "called" ;
    if (ui->UserNameInput->text().isEmpty() || ui->UserPasswordInput->text().isEmpty()) {
        enrollNotification("用户名和密码不能为空");
    } else {
        int userID = Global::instance().getGlobalUserManage()->Create(ui->UserNameInput->text(), ui->UserPasswordInput->text());
        if(userID != -1){
            Global::instance().getGlobalDataBase()->setTotalvalue(userID, 64800);
            enrollNotification("注册成功，请点击确认返回登录");
            Login* l = new Login();
            l->show();
            this->close();
        } else {
            enrollNotification("用户名已存在，请更换用户名");
        }
    }
}
void enroll::keyPressEvent(QKeyEvent  *event)
{
    switch(event->key()){
    case Qt::Key_Return:
        on_registerButton_clicked();
        break;
    case Qt::Key_Enter:
         on_registerButton_clicked();
        break;
    default:
        break;
    }
}

