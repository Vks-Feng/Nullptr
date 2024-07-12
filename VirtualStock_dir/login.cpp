#include "login.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
    this->setWindowFlags(Qt::FramelessWindowHint);
    connect(ui->DetailButton,&QPushButton::clicked,[=](){
        QMessageBox::information(this,"详情","敬请期待");
    });

    connect(Global::instance().getGlobalClient(), &ClientSocket::signal_Receive_connectToDataBase, this, &Login::connectToDataBase);

    connect(Global::instance().getGlobalClient(), &ClientSocket::signal_Receive_Login, this, &Login::readyToLogin);

    connect(Global::instance().getGlobalClient(), &ClientSocket::signal_Receive_Relogin, [=](){
        loginErrorNotification("已在其他设备上登录");
    });


    connect(ui->loginCloseButton,&QPushButton::clicked,[=](){
        this->close();
    });
    connect(ui->loginMinimumButton,&QPushButton::clicked,[=](){
        this->showMinimized();
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
    qDebug() << "0";
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
            qDebug() << "vks1";
            User test = Global::instance().getGlobalDataBase()->enableUser(ui->UserNameInput->text());
            qDebug() << "vks2";
            int userID = test.GetId();
            qDebug() << "vks3";
            QString msg = QString("Login:%1").arg(userID);
            Global::instance().getGlobalClient()->write(msg.toUtf8());
            Global::instance().getGlobalClient()->waitForBytesWritten();
            qDebug() << "vks4";
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

void Login::on_RegisterButton_clicked(){
    enroll* en =new enroll();
    this->close();
    en->show();
}

void Login::connectToDataBase(QString ip, QString _password){
    const char* host = ip.toUtf8().constData(); // MySQL server host
    const char* user = "visitor_1"; // MySQL username
    const char* password = _password.toUtf8().constData(); // MySQL password
    const char* database = "stocks"; // MySQL database name
    unsigned int port = 3306; // MySQL port (default is 3306)
    const char* unix_socket = nullptr; // Unix socket (can be nullptr for TCP/IP)
    unsigned long client_flag = 0; // Connection flags (usually 0)
    BackDB* db = new BackDB(host, user, password, database, port, unix_socket, client_flag);
    Global::instance().setGlobalDataBase(db);
    qDebug() << "vks database";
}

void Login::readyToLogin(){
    Global::instance().getGlobalUserManage()->UserAdd(Global::instance().getGlobalDataBase()->enableUser(ui->UserNameInput->text()));
    MainWindow* main = new MainWindow;
    main->show();
    this->close();
}


