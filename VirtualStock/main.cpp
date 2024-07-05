#include "widget.h"
#include "login.h"
#include "usermanage.h"

#include <QApplication>

UserManage* um = nullptr;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    um = new UserManage();
    Login l;
    l.show();
    return a.exec();
}
