#include "widget.h"
#include "login.h"
#include "global.h"
//#include "kcharts.h"
#include <QApplication>

UserManage* um = nullptr;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

   UserManage* um = new UserManage;
   Global::instance().setGlobalUserManage(um);
//   BackDB* db = new BackDB;
//   Global::instance().setGlobalDataBase(db);
   ClientSocket* client = new ClientSocket();
   client->connectToHost("120.26.82.216", 12345);
   client->setSocketOption(QAbstractSocket::KeepAliveOption, 1);
   Global::instance().setGlobalClient(client);
   Global::instance().getGlobalClient()->write("ConnectDB:");
   Login* l = new Login();
   l->show();


//    Kcharts test;
//    test.ChangeStock(3);

//       BackDB b;
//       b.test();

    return a.exec();
}
