#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QWidget>
#include <QDebug>
#include <QObject>
#include <QDateTime>
#include <QMessageBox>
#include "server.h"

namespace Ui {
class TcpServer;
}

class TcpServer : public QWidget
{
    Q_OBJECT

public:
    explicit TcpServer(QWidget *parent = nullptr);

    void Notification(QString notice);

    void addOnlineClient(long long int descriptor);

    void removeOnlineClient(long long int descriptor);

    void updateCurrentClientNum();

    ~TcpServer();

signals:


public slots:
    void createServer();

    void handleConnectedMessage(QString& message, long long int descriptor);

    void handleDisconnectedMessage(QString& message, long long int descriptor);

    void handleReceivedMessage(QString& msg, long long int descriptor);

    void showDebugMessage(const QString& msg);

    void sendMessage();

private:
    Ui::TcpServer *ui;

//    QHostAddress ipAddress;

//    int port;

    Server* server = nullptr;

    bool serverStatus = false;

};

#endif // TCPSERVER_H
