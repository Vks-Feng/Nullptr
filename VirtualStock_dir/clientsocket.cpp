#include "clientsocket.h"

ClientSocket::ClientSocket(QObject *parent) : QTcpSocket(parent)
{
    // 设置心跳包定时器
    QTimer *heartbeatTimer = new QTimer;
    connect(heartbeatTimer, &QTimer::timeout, this, &ClientSocket::sendHeartbeat);
    heartbeatTimer->start(10000); // 每10秒发送一次心跳包
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

void ClientSocket::sendHeartbeat() {
    if (state() == QAbstractSocket::ConnectedState) {
        QByteArray heartbeat = "HEARTBEAT";
        write(heartbeat);
        flush();
    }
}

void ClientSocket::onReadyRead()
{
    QByteArray data = readAll();
    processMessage(data);
}

void ClientSocket::sendRequest_toServer(const QString &request)
{
    if(state() == QAbstractSocket::ConnectedState){
        write(request.toUtf8());
    }
}

//void ClientSocket::sendRequest_ConnectToDataBase(){
//    qDebug() << "sending DB";
//    sendRequest_toServer("ConnectDB:");
//}

//发送登录请求
void ClientSocket::sendRequest_Login(const int& userID){
    sendRequest_toServer(QString("Login:%1").arg(userID));
}

void ClientSocket::sendRequest_Refresh(){
    sendRequest_toServer("Refresh:");
}

////发送信息请求到服务器
//void ClientSocket::sendRequest_sendMessage(const QString& userID, const QString& content)
//{
//    QString request = "sendMessage" + userID + "," + content;
//    sendRequest_toServer(request);
//    sendRequest_Broadcast(userID);
//}

////发送广播请求到服务器
//void ClientSocket::sendRequest_Broadcast(const QString& userID)
//{
//    QString request = "sendMessage" + userID;
//    sendRequest_toServer(request);
//}

void ClientSocket::processMessage(const QByteArray &data)
{
    QString message = QString::fromUtf8(data);
    // qDebug() << "server: " << message;
    handleCommand_fromServer(message);
}

void ClientSocket::handleCommand_fromServer(const QString &command){
    // 拆分请求类型和参数
    int separatorIndex = command.indexOf(':');
    if (separatorIndex == -1) {
        handleCommand_Unknown();
        return;
    }
    QString commandType = command.left(separatorIndex);
    QString parametersString = command.mid(separatorIndex + 1);

    qDebug() << "vks-server-commandType:" << commandType;

    // 拆分参数
    QStringList parameters = parametersString.split(',');

    // 根据请求类型调用相应的处理函数
    if (commandType == "RefreshPost") {
        handleCommand_Refresh();
    } else if (commandType == "Relogin") {
        handleCommand_Relogin();;
    } else if (commandType == "Login") {
        handleCommand_Login();
    } else if (commandType == "ConnectDB") {
        handleCommand_connectToDataBase(parameters);
    } else if (commandType == "RefreshSonPost") {
        handleCommand_RefreshSonPost();
    } else {
        handleCommand_Unknown();
    }
}

void ClientSocket::handleCommand_connectToDataBase(const QStringList &parameters){
    qDebug() << "vks-server: ready to connect to database";
    emit signal_Receive_connectToDataBase(parameters[0], parameters[1]);
}

void ClientSocket::handleCommand_Login() {
    qDebug() << "vks-server: ready to login";
    emit signal_Receive_Login();
}

void ClientSocket::handleCommand_Relogin(){
    qDebug() << "vks-server: already logined";
    emit signal_Receive_Relogin();
}

void ClientSocket::handleCommand_Refresh() {
    qDebug() << "vks-server: ready to refresh";
    emit signal_Receive_Refresh();
}

void ClientSocket::handleCommand_RefreshSonPost() {
    qDebug() << "vks-server: ready to refresh son post";
    emit signal_Receive_RefreshSonPost();
}

//void ClientSocket::handleCommand_Broadcast(const QStringList &parameters) {
//    qDebug() << "vks-server: ready to broadcast";
//    QString userName = parameters.value(0);
//    QString content = parameters.value(1);
//    QString show = QString("%1: %2").arg(userName, content);
//    qDebug() << "vks-server:" << show;
//    emit signal_Receive_Broadcast(userName, content);
//}

void ClientSocket::handleCommand_Unknown() {
    QString response = "vks-server: Unknown request";
    qDebug() << response;
}

