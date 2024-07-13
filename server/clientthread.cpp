#include "clientthread.h"

clientThread::clientThread(TcpClientSocket* clientSocket, QObject *parent)
    : QThread{parent}
{
    client = clientSocket;
}

void clientThread::run(){
    //connect(client, &TcpClientSocket::signal_ReceiveMessageFromClients, this, &clientThread::handleRequest);
    connect(client, &TcpClientSocket::signal_Disconnected, this, &clientThread::thread_slot_disconnect);
    connect(client, &TcpClientSocket::signal_Receive_ConnectToDataBase, this, &clientThread::thread_slot_connectDB);
    connect(client, &TcpClientSocket::signal_Receive_Login, this, &clientThread::thread_signal_received_loginRequest);
    connect(client, &TcpClientSocket::signal_Receive_Refresh, this, &clientThread::thread_signal_received_refreshRequest);
    connect(client, &TcpClientSocket::signal_Receive_RefreshSonPost, this, &clientThread::thread_signal_received_refreshSonPostRequest);
    connect(client, &TcpClientSocket::signal_Receive_Debug, this, &clientThread::thread_signal_received_debug);
    exec();
}

TcpClientSocket* clientThread::getClient(){
    return client;
}

void clientThread::thread_slot_disconnect(long long int descriptor){
    emit thread_signal_disconnected(client->GetClientSocketDescriptor());
    client->destroyed();
    qDebug() << "disconnect";
    quit();
    this->destroyed();
}

//void clientThread::thread_slot_received_loginRequest(int userID){
//    client->SetUserID(userID);
//}

void clientThread::thread_slot_connectDB(){
    QString loginCommand = "ConnectDB:" + QString("rm-n4a8f71b4zhg4w616co.mysql.cn-wuhan-lr.rds.aliyuncs.com") + "," + QString("Lin123456");
    client->write(loginCommand.toUtf8());
}

void clientThread::handleRequest(QString& request){
    QString clientInfo = QString("[%1:%2]:").arg(client->GetClientIP()).arg(client->GetClientPort());
    // 拆分请求类型和参数
    int separatorIndex = request.indexOf(':');
    if (separatorIndex == -1) {
        qDebug() << clientInfo + "unknow request";
        return;
    }
    QString requestType = request.left(separatorIndex);
    QString parametersString = request.mid(separatorIndex + 1);

    qDebug() << "vks-client-requestType:" << requestType;

    // 拆分参数
    QStringList parameters = parametersString.split(',');

    // 根据请求类型调用相应的处理函数
    if (requestType == "Refresh") {
        emit thread_signal_received_refreshRequest(client->GetClientSocketDescriptor());
    } else if (requestType == "Login") {
        emit thread_signal_received_loginRequest(client->GetUserID(), client->GetClientSocketDescriptor());
    } else {
        qDebug() << "unknow request";
    }
}


