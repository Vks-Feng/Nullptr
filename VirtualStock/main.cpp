#include "widget.h"
#include "login.h"
#include "querywidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login l;
    l.show();
    QueryWidget q;
    q.show();
    return a.exec();
}
