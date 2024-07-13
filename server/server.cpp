#include "server.h"
#include "clientthread.h"

Server::Server(QObject *parent, int _port) : QTcpServer(parent)
{
    this->port = _port;
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    //创建客户端的套接字（以服务器类为父类，即可实现服务器生命周期结束前自动回收客户端套接字）
    TcpClientSocket *tcpClientSocket = new TcpClientSocket(this);
    //根据传入的套接字 描述符（一个唯一的网络标识符） 构建套接字，从而实现客户端与服务器的连接
    tcpClientSocket->setSocketDescriptor(socketDescriptor);

    QString clientIP = tcpClientSocket->peerAddress().toString();
    quint16 clientPort = tcpClientSocket->peerPort();
    tcpClientSocket->SetClientCocketDescriptor(socketDescriptor);
    tcpClientSocket->SetClientIP(clientIP);
    tcpClientSocket->SetClientPort(clientPort);

    QString clientConnectInfo = QString("[%1:%2]:成功连接").arg(clientIP).arg(clientPort);

    clientThread* newThread = new clientThread(tcpClientSocket);
    //把该套接字放入服务器类的客户端套接字数组中
    tcpclientsocketlist.append(newThread);
    //客户端套接字触发接收信息的信号链式出发服务器接收信息的信号
    //connect(newThread, &clientThread::thread_signal_received, this, &Server::signal_ReceiveMessage);
    //客户端断开连接的信号触发自定义的断连信号（为了传递套接字的标识符），自定义的断连信号触发服务器断开与客服端连接的函数，并且发出断连的信号
    connect(newThread, &clientThread::thread_signal_disconnected, this, &Server::clientDisconnected);
    connect(newThread, &clientThread::thread_signal_received_loginRequest, this, &Server::handleRequest_Login);
    connect(newThread, &clientThread::thread_signal_received_refreshRequest, this, &Server::handleRequest_Refresh);
    connect(newThread, &clientThread::thread_signal_received_refreshSonPostRequest, this, &Server::handleRequest_sonPostRefresh);
    connect(newThread, &clientThread::thread_signal_received_debug, this, &Server::signal_showDebugMessage);
    newThread->start();
    //发出信号，有客户端建立连接
    emit signal_ClientConnected(clientConnectInfo, tcpClientSocket->socketDescriptor());
}

void Server::sendMessageToClients(QString& message, long long int descriptor)
{
    //找到指定的客服端并发送信息
    for (clientThread* thread : tcpclientsocketlist)
    {
        thread->getClient()->write(message.toUtf8());
        qDebug() << "成功发送！";
    }
}

void Server::clientDisconnected(long long int descriptor) {
    QString clientDisconnectInfo = getClientInfo(descriptor) + "断开连接";
    //找到对应的客户端套接字并从数组中移除
    for (int i = 0; i < tcpclientsocketlist.size(); ++i) {
        clientThread* thread = tcpclientsocketlist[i];
        if (thread->getClient()->GetClientSocketDescriptor() == descriptor) {
            // 删除该client
            tcpclientsocketlist.removeAt(i);
            qDebug() << "从数组中移除";
            thread->getClient()->deleteLater(); // 延迟删除对象，确保所有信号槽处理完毕
            break;
        }
    }
    // 发出信号，有客户端断连
    emit signal_ClientDisconnected(clientDisconnectInfo, descriptor);
}

QString Server::getClientIP(long long int descriptor){
    for (clientThread* thread : tcpclientsocketlist)
    {
        if(thread->getClient()->GetClientSocketDescriptor() == descriptor){
            return thread->getClient()->peerAddress().toString();
        }
    }
    return "Can not find";
}

quint16 Server::getClientPort(long long int descriptor){
    for (clientThread* thread : tcpclientsocketlist)
    {
        if(thread->getClient()->GetClientSocketDescriptor() == descriptor){
            return thread->getClient()->peerPort();
        }
    }
    return 0;
}

int Server::getClientID(long long descriptor){
    for (clientThread* thread : tcpclientsocketlist)
    {
        if(thread->getClient()->GetClientSocketDescriptor() == descriptor){
            return thread->getClient()->GetUserID();
        }
    }
    return -1;
}

QString Server::getClientInfo(long long int descriptor){
    QString clientIP = "cannotFind";
    quint16 clientPort = 0;
    int clientUserID = -1;
    for (clientThread* thread : tcpclientsocketlist)
    {
        if(thread->getClient()->GetClientSocketDescriptor() == descriptor){
            clientIP = getClientIP(descriptor);
            clientPort = getClientPort(descriptor);
            clientUserID = getClientID(descriptor);
        }
    }
    return QString("[%1:%2]UserID:%3:").arg(clientIP).arg(clientPort).arg(clientUserID);
}

bool Server::isUserOnline(int userID, long long int descriptor){
    for (clientThread* thread : tcpclientsocketlist)
    {
        if(thread->getClient()->GetUserID() == userID && thread->getClient()->GetClientSocketDescriptor() != descriptor){
            return true;
        }
    }
    return false;
}

void Server::handleRequest_Login(int userID, long long int descriptor){
    if(!isUserOnline(userID, descriptor)){
        QString loginCommand = "Login:";
        for(clientThread* thread : tcpclientsocketlist){
            if(thread->getClient()->GetClientSocketDescriptor() == descriptor){
                thread->getClient()->write(loginCommand.toUtf8());
                qDebug() << "Login成功发送！";
                emit signal_showDebugMessage(QString("Target:%1 Login成功发送！").arg(thread->getClient()->GetUserID()));
            }
        }
    }else{
        QString loginCommand = "Relogin:";
        for(clientThread* thread : tcpclientsocketlist){
            if(thread->getClient()->GetClientSocketDescriptor() == descriptor){
                thread->getClient()->write(loginCommand.toUtf8());
                qDebug() << "Relogin成功发送！";
                emit signal_showDebugMessage(QString("Target:%1 ReLogin成功发送！").arg(thread->getClient()->GetUserID()));
            }
        }
    }
}

void Server::handleRequest_sonPostRefresh(){
    for (clientThread* thread : tcpclientsocketlist)
    {
        thread->getClient()->write("RefreshSonPost:");
        qDebug() << "RefreshSonPost成功发送！";
        emit signal_showDebugMessage(QString("Target:%1 RefreshSonPost成功发送！").arg(thread->getClient()->GetUserID()));
    }
}

void Server::handleRequest_Refresh(){
    for (clientThread* thread : tcpclientsocketlist)
    {
        thread->getClient()->write("RefreshPost:");
        qDebug() << "Refresh成功发送！";
        emit signal_showDebugMessage(QString("Target:%1 Refresh成功发送！").arg(thread->getClient()->GetUserID()));
    }
}


