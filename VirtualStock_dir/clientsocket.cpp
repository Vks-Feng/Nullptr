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

void ClientSocket::onReadyRead()
{
    QByteArray data = readAll();
    processMessage(data);
}

void ClientSocket::sendRequest_toServer(const QString &request)
{
    if (state() == QAbstractSocket::ConnectedState)
    {
        write(request.toUtf8());
    }
}

//发送登录请求
void ClientSocket::sendRequest_Login(const QString& userID){
    QString request = "Login:" + userID;
    sendRequest_toServer(request);
}

//发送信息请求到服务器
void ClientSocket::sendRequest_sendMessage(const QString& userID, const QString& content)
{
    QString request = "sendMessage" + userID + "," + content;
    sendRequest_toServer(request);
    sendRequest_Broadcast(userID);
}

//发送广播请求到服务器
void ClientSocket::sendRequest_Broadcast(const QString& userID)
{
    QString request = "sendMessage" + userID;
    sendRequest_toServer(request);
}

void ClientSocket::processMessage(const QByteArray &data)
{
    QString message = QString::fromUtf8(data);
    //qDebug() << "server: " << message;
    handleCommand_fromServer(message);
}

void ClientSocket::handleCommand_fromServer(const QString &command){
    // 拆分请求类型和参数
    int separatorIndex = command.indexOf(':');
    if (separatorIndex == -1) {
        handleUnknownRequest();
        return;
    }
    QString commandType = command.left(separatorIndex);
    QString parametersString = command.mid(separatorIndex + 1);

    qDebug() << "vks-server-commandType:" << commandType;

    // 拆分参数
    QStringList parameters = parametersString.split(',');

    // 根据请求类型调用相应的处理函数
    if (commandType == "Refresh") {
        handleCommand_Refresh();
    } else if (commandType == "Broadcast") {
        handleCommand_Broadcast(parameters);
    } else if (commandType == "Login") {
        handleCommand_Login();
    } else {
        handleUnknownRequest();
    }
}

void ClientSocket::handleCommand_Login() {
    qDebug() << "vks-server: ready to login";
    emit signal_Receive_Login();
}

void ClientSocket::handleCommand_Refresh() {
    qDebug() << "vks-server: ready to refresh";
    emit signal_Receive_Refresh();
}

void ClientSocket::handleCommand_Broadcast(const QStringList &parameters) {
    qDebug() << "vks-server: ready to broadcast";
    QString userName = parameters.value(0);
    QString content = parameters.value(1);
    QString show = QString("%1: %2").arg(userName, content);
    qDebug() << "vks-server:" << show;
    emit signal_Receive_Broadcast(userName, content);
}

void ClientSocket::handleUnknownRequest() {
    QString response = "vks-server: Unknown request";
    qDebug() << response;
}

