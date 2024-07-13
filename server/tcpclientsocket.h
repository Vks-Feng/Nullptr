#ifndef TCPCLIENTSOCKET_H
#define TCPCLIENTSOCKET_H

#include <QTcpSocket>//通讯套接字
#include <QObject>

class TcpClientSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit TcpClientSocket(QObject *parent = nullptr);

    void SetClientCocketDescriptor(qintptr descriptor);

    qintptr GetClientSocketDescriptor();

    void SetClientSocketDescriptor();

    QString GetClientIP();

    void SetClientIP(QString _ip);

    quint16 GetClientPort();

    void SetClientPort(quint16 _port);

    int GetUserID();

    void SetUserID(int _userID);

    void handleRequest(QString& data);

signals:
    //从客户端接收到信息，去解析之后分析出客户端的请求后，发出不同的请求，从而触发线程中的不同的信号
    void signal_ReceiveMessageFromClients(QString&);

    //接收到断开连接的信号
    void signal_Disconnected(long long int);

    //连接服务器的请求
    void signal_Receive_ConnectToDataBase();

    //接收到登录请求
    void signal_Receive_Login(int userID, long long int);

    //接收到登录初始化
    void signal_Receive_LoginInit(int userID);

    //接收到刷新请求
    void signal_Receive_Refresh(long long int);

    //接收到刷新字帖请求
    void signal_Receive_RefreshSonPost(long long int);

    //接受到未知请求
    void signal_Receive_Unknown(long long int);

    //接收debug信息
    void signal_Receive_Debug(const QString& msg);

protected slots:
    //接受数据
    void readReceivedData();

    //用户断开
    void clientDisconnected();

private:
    qintptr clientSocketDescriptor;

    QString clientIP;

    quint16 clientPort;

    int userID = -1;
};

#endif // TCPCLIENTSOCKET_H

