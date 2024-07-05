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
