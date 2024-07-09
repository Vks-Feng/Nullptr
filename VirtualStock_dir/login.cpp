#include "login.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
    connect(ui->DetailButton,&QPushButton::clicked,[=](){
        QMessageBox::information(this,"详情","敬请期待");
    });
}

Login::~Login()
{
    delete ui;
}

void Login::loginErrorNotification(QString error){
    QMessageBox msgBox;
    msgBox.setText(error);
    msgBox.exec();
}

void Login::on_LoginButton_clicked()
{
    if (ui->UserNameInput->text().isEmpty() || ui->UserPasswordInput->text().isEmpty()) {
        loginErrorNotification("用户名或密码不能为空");
    } else {
        int LoginResult = Global::instance().getGlobalUserManage()->Check(ui->UserNameInput->text(), ui->UserPasswordInput->text());
        switch (LoginResult) {
        case 0:
        {
            loginErrorNotification("vks：该用户名不存在，而且老子暂时懒得设计所以你tm必须给老子注册去");
            enroll* en = new enroll(); // 设置父对象为当前窗口
            this->close();
            en->show();
            break;
        }
        case 1:
        {
            loginErrorNotification("账号或密码错误");
            break;
        }
        case 2:
        {
            Global::instance().getGlobalUserManage()->UserAdd(Global::instance().getGlobalDataBase()->enableUser(ui->UserNameInput->text()));
            MainWindow* mainwindow = new MainWindow(); // 设置父对象为当前窗口
            mainwindow->show();

            this->close();
            break;
        }
        default:
            break;
        }
    }
}

void Login::keyPressEvent(QKeyEvent  *event)
{
    switch(event->key()){
    case Qt::Key_Return:
        on_LoginButton_clicked();
        break;
    case Qt::Key_Enter:
        on_LoginButton_clicked();
        break;
    default:
        break;
    }
}

void Login::on_RegisterButton_clicked()
{
    enroll* en =new enroll();
    this->close();
    en->show();
}



