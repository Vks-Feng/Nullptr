#include "widget.h"
#include "login.h"
#include "global.h"
#include "querywidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UserManage* um = new UserManage;
    Global::instance().setGlobalVar(um);
    Login* l = new Login();
    l->show();
//    QueryWidget q;
//    q.show();
    return a.exec();
}
