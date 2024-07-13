#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QList>
#include <QObject>
#include "clientthread.h"

class Server : public QTcpServer
{
    Q_OBJECT
public:
    friend class TcpServer;
    //指定父对象，在实际应用时，我指定服务器窗口为父对象，可以实现窗口关闭时对Server开辟空间的回收
    explicit Server(QObject *parent = nullptr, int port = 0);

    //Server会持续进行监听(监听套接字）
    //与其构建连接的客户端的套接字（通信套接字）会被存储在该套接字数组中
    QList<clientThread*> tcpclientsocketlist;

    //用于获取指定客户端的IP
    QString getClientIP(long long int descriptor);

    //用于获取指定客户端的端口
    quint16 getClientPort(long long int descriptor);

    int getClientID(long long int descriptor);

    QString getClientInfo(long long int descriptor);

    bool isUserOnline(int userID, long long int descriptor);


signals:    
    //客户端连接的信号
    void signal_ClientConnected(QString& clientConnectedInfo,long long int);

    //客户端断开连接的信号
    void signal_ClientDisconnected(QString& clientDisconnectedInfo,long long int descriptor);

    //接收到信息的信号（后续会设计更多类似接收信息的信号，来用于处理不同请求）
    void signal_ReceiveMessage(QString& msg, long long int descriptor);

    void signal_Receive_Login(int userID, long long int descriptor);

    void signal_Receive_Refresh(int userID, long long int descriptor);

    void signal_showDebugMessage(const QString& msg);

public slots:
    //用于向指定的客户端发送消息
    void sendMessageToClients(QString& msg, long long int descriptor);

    //接收到客户端的断开连接信号后触发，用于移除在List中的该客户端
    void clientDisconnected(long long int descriptor);

    //展示 “何时” 收到了 “谁” 发来的 “什么请求”
    //void showReceiveMessage(QString& msg, long long int descriptor);

    //处理登录请求
    void handleRequest_Login(int userID, long long int descriptor);

    //处理刷新请求
    void handleRequest_Refresh();

    //处理刷新字帖请求
    void handleRequest_sonPostRefresh();

protected:
    //1.在与客户端建立连接时，把该客户端的套接字添加到Server的套接字数组中
    //2.绑定相应的槽函数
    //3.发出建立连接的信号
    void incomingConnection(qintptr socketDescriptor) override;

private:
    int port = 12345;

    QHostAddress ipAddress = QHostAddress::Any;

//    const char* host = "rm-n4a8f71b4zhg4w616co.mysql.cn-wuhan-lr.rds.aliyuncs.com";

//    const char* password = "Lin123456";
};

#endif // SERVER_H


