#include "tcpclientsocket.h"

TcpClientSocket::TcpClientSocket(QObject *parent) : QTcpSocket(parent)
{
    connect(this, &QTcpSocket::readyRead, this, &TcpClientSocket::readReceivedData);
    connect(this, &TcpClientSocket::signal_ReceiveMessageFromClients, this, &TcpClientSocket::handleRequest);
    connect(this, &QTcpSocket::disconnected, this, &TcpClientSocket::clientDisconnected);
}

void TcpClientSocket::readReceivedData()
{
    while (bytesAvailable() > 0)
    {
        QString data = QString(readAll());
        qDebug() << "origin:" << data;
        if(data != "HEARTBEAT"){
            emit signal_Receive_Debug(QString("%1 origin content: %2").arg(userID).arg(data));
            emit signal_ReceiveMessageFromClients(data);
        }
    }
}

void TcpClientSocket::clientDisconnected()
{
    emit signal_Disconnected(this->GetClientSocketDescriptor());
}

void TcpClientSocket::SetClientCocketDescriptor(qintptr descriptor){
    this->clientSocketDescriptor = descriptor;
}

qintptr TcpClientSocket::GetClientSocketDescriptor(){
    return this->clientSocketDescriptor;
}

QString TcpClientSocket::GetClientIP(){
    return clientIP;
}

void TcpClientSocket::SetClientIP(QString _ip){
    clientIP = _ip;
}

quint16 TcpClientSocket::GetClientPort(){
    return clientPort;
}

void TcpClientSocket::SetClientPort(quint16 _port){
    clientPort = _port;
}

int TcpClientSocket::GetUserID(){
    return userID;
}

void TcpClientSocket::SetUserID(int _userID){
    userID = _userID;
}

void TcpClientSocket::handleRequest(QString& request){
    QString clientInfo = QString("[%1:%2]UserID%3:").arg(clientIP).arg(clientPort).arg(userID);
    // 拆分请求类型和参数
    int separatorIndex = request.indexOf(':');
    if (separatorIndex == -1) {
        emit signal_Receive_Debug(clientInfo + "unknow request");
        qDebug() << clientInfo + "unknow request";
        return;
    }
    QString requestType = request.left(separatorIndex);
    QString parametersString = request.mid(separatorIndex + 1);

    qDebug() << "vks-client-requestType:" << requestType;

    // 拆分参数
    QStringList parameters = parametersString.split(',');

    // 根据请求类型调用相应的处理函数
    if (requestType == "RefreshPost") {
        qDebug() << clientInfo + "request for refresh";
        emit signal_Receive_Debug(clientInfo + "request for refresh");
        emit signal_Receive_Refresh(clientSocketDescriptor);
    } else if (requestType == "Login") {
        this->userID = parameters[0].toInt();
        qDebug() << clientInfo + "request for login";
        emit signal_Receive_Debug(clientInfo + "request for login");
        emit signal_Receive_Login(userID, clientSocketDescriptor);
    } else if (requestType == "ConnectDB") {
        qDebug() << clientInfo + "request for DataBase";
        emit signal_Receive_Debug(clientInfo + "request for DataBase");
        emit signal_Receive_ConnectToDataBase();
    } else if (requestType == "RefreshSonPost") {
        emit signal_Receive_Debug(clientInfo + "request for refresh sonpost");
        emit signal_Receive_RefreshSonPost(clientSocketDescriptor);
    } else if (requestType == "HERATBEAT") {

    } else {
        emit signal_Receive_Unknown(clientSocketDescriptor);
    }
}
