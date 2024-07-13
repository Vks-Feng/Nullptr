#include "widget.h"
#include "tcpserver.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TcpServer* t = new TcpServer();
    t->show();
    return a.exec();
}
