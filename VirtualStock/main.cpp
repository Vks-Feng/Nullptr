#include "widget.h"
#include "login.h"
<<<<<<< HEAD
#include "global.h"
#include "querywidget.h"
=======
#include "usermanage.h"
>>>>>>> a9b89b36e241c5019cc123393d20395c9374dba1

#include <QApplication>

UserManage* um = nullptr;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
<<<<<<< HEAD
    UserManage* um = new UserManage;
    Global::instance().setGlobalVar(um);
    Login* l = new Login();
    l->show();
//    QueryWidget q;
//    q.show();
=======
    um = new UserManage();
    Login l;
    l.show();
>>>>>>> a9b89b36e241c5019cc123393d20395c9374dba1
    return a.exec();
}
