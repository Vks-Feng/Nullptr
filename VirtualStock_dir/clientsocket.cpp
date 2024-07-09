#include "clientsocket.h"

ClientSocket::ClientSocket(QObject *parent) : QTcpSocket(parent)
{
    connect(this, &QTcpSocket::readyRead, this, &ClientSocket::onReadyRead);
}

void ClientSocket::connectToServer(const QString &host, int port)
{
    if (state() == QAbstractSocket::ConnectedState) {
        disconnectFromHost();
        waitForDisconnected();
    }
    connectToHost(host, port);
}

void ClientSocket::sendMessage(const QString &message)
{
    if (state() == QAbstractSocket::ConnectedState)
    {
        write(message.toUtf8());
    }
}

void ClientSocket::onReadyRead()
{
    QByteArray data = readAll();
    processMessage(data);
}

void ClientSocket::processMessage(const QByteArray &data)
{
    QString message = QString::fromUtf8(data);
    qDebug() << message;
//    emit messageReceived(message);
}


