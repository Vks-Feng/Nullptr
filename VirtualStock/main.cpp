#include "widget.h"
//#include "login.h"
//#include "usermanage.h"
//#include "querywidget.h"
#include "backdb.h"

//

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BackDB b;
    b.testEnableUser();

    return a.exec();
}
