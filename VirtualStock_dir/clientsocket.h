#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QTcpSocket>
#include <QObject>
#include <QTimer>

class ClientSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit ClientSocket(QObject *parent = nullptr);

    //连接到服务器
    void connectToServer(const QString &host, int port);

    //发送请求到服务器
    void sendRequest_toServer(const QString &request);

    void sendRequest_ConnectToDataBase();

    //发送登录请求
    void sendRequest_Login(const int& userID);

    //给服务器里的套接字赋值（值为userID）
    void sendRequest_LoginInit(const int& userID);

    //发送更新请求
    void sendRequest_Refresh();

//    //发送信息请求到服务器
//    void sendRequest_sendMessage(const QString& userID, const QString& content);

//    //发送广播请求到服务器
//    void sendRequest_Broadcast(const QString& userID);

    //处理服务器发来命令
    void handleCommand_fromServer(const QString &command);

    //连接到数据库
    void handleCommand_connectToDataBase(const QStringList &parameters);

    //处理登录命令
    void handleCommand_Login();

    //处理多号在线问题
    void handleCommand_Relogin();

    //处理服务器发来的刷新命令
    void handleCommand_Refresh();

    //处理服务器发来的刷新字帖命令
    void handleCommand_RefreshSonPost();

    //处理服务器发来的广播命令
    //void handleCommand_Broadcast(const QStringList &parameters);

    //处理错误指令
    void handleCommand_Unknown();

signals:

    void signal_MessageReceived(QString& message);

    void signal_Receive_connectToDataBase(QString ip, QString password);

    void signal_Receive_Login();

    void signal_Receive_Relogin();

    void signal_Receive_Refresh();

    void signal_Receive_RefreshSonPost();

    void signal_Receive_Broadcast(QString& userName, QString& content);

private slots:
    void onReadyRead();

    void sendHeartbeat();

private:
    void processMessage(const QByteArray &data);
};

#endif // CLIENTSOCKET_H
