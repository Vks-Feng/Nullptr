#include "widget.h"
#include "login.h"
#include "global.h"
#include "backdb.h"

#include <QApplication>

UserManage* um = nullptr;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

   UserManage* um = new UserManage;
   Global::instance().setGlobalUserManage(um);
   BackDB* db = new BackDB;
   Global::instance().setGlobalDataBase(db);
   Login* l = new Login();
   l->show();

<<<<<<< HEAD
     // BackDB b;
     // b.test();
=======
    //  BackDB b;
    // b.test();
>>>>>>> 0a9832cafe567b3547e892bf60e7b50d94323ff5

    return a.exec();
}
