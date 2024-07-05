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

<<<<<<< HEAD
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
            MainWindow* mainwindow = new MainWindow(); // 设置父对象为当前窗口
            mainwindow->show();
            Global::instance().getGlobalUserManage()->UserAdd(User());
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
=======
void Login::on_LoginButton_clicked()
{
    bool Loginsuccess = (ui->UserNameInput->text() == "vks") && (ui->UserPasswordInput->text() == "123");
    if(Loginsuccess) {
        MainWindow* mainwindow = new MainWindow();
        mainwindow->show();
        this->close();
    } else if(ui->UserPasswordInput->text() != "123") {
        QMessageBox msgBox;
        msgBox.setText("密码错误");
        msgBox.exec();
    }
>>>>>>> a9b89b36e241c5019cc123393d20395c9374dba1
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

int Login::CheckUser(QString name, QString password)
{
    QString dataBaseName = "vks";
    QString dataBasePassword = "123";
    if(name == dataBaseName && dataBasePassword == dataBasePassword){
        return true;
    }
    else
    {
        return false;
    }
}
