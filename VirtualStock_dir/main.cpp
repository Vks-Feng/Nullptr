#include "widget.h"
#include "login.h"
#include "global.h"
#include <QApplication>

UserManage* um = nullptr;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    UserManage* um = new UserManage;
//    Global::instance().setGlobalUserManage(um);
//    BackDB* db = new BackDB;
//    Global::instance().setGlobalDataBase(db);
//    ClientSocket* client = new ClientSocket();
//    Global::instance().setGlobalClient(client);
//    Login* l = new Login();
//    l->show();

<<<<<<< HEAD

      BackDB b;
      b.test();
=======
//      BackDB b;
//      b.test();
>>>>>>> 7a31ade3c1a2e5e255970f42846cc46cf53d9fda

    return a.exec();
}
