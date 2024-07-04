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

void enroll::on_LoginButton_clicked()
{
    if (ui->UserNameInput->text().isEmpty() || ui->UserPasswordInput->text().isEmpty()) {
        enrollNotification("用户名和密码不能为空");
    } else {
        if(Global::instance().getGlobalUserManage()->Create(ui->UserNameInput->text(), ui->UserPasswordInput->text())){
            enrollNotification("注册成功，请点击确认返回登录");
            Login* l = new Login();
            l->show();
            this->close();
        }
    }
}

