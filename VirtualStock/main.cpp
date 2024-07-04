#include "widget.h"
#include "login.h"
#include "usermanage.h"
#include "querywidget.h"

#include <QApplication>

UserManage* um = nullptr;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    um = new UserManage();
    QueryWidget q;
    q.show();
    return a.exec();
}
