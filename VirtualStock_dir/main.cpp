#include "widget.h"
#include "login.h"
#include "global.h"
//#include "backdb.h"
#include <QApplication>
#include "istmcharts.h"

UserManage* um = nullptr;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    UserManage* um = new UserManage;
    Global::instance().setGlobalUserManage(um);

    BackDB* b = new BackDB;
    Global::instance().setGlobalDataBase(b);

    ClientSocket* client = new ClientSocket();
    client->connectToHost("120.26.82.216", 12345);
    client->setSocketOption(QAbstractSocket::KeepAliveOption, 1);

    Global::instance().setGlobalClient(client);
    Global::instance().getGlobalClient()->write("ConnectDB:");

    Login* l = new Login();
    l->show();

//    BackDB b;
//    b.test();

//    IstmCharts test;
//    test.show();

    return a.exec();
}
