#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QTcpSocket>
#include <QObject>

class ClientSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit ClientSocket(QObject *parent = nullptr);

    void connectToServer(const QString &host, int port);

    void sendMessage(const QString &message);

    void handleServerCommand(const QString &command);

signals:
    void messageReceived(QString message);

private slots:
    void onReadyRead();

private:
    void processMessage(const QByteArray &data);
};

#endif // CLIENTSOCKET_H
