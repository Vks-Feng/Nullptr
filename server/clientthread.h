#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H

#include <QThread>
#include "tcpclientsocket.h"

class Server;

class clientThread : public QThread
{
    Q_OBJECT
public:
    explicit clientThread(TcpClientSocket* clientSocket, QObject *parent = nullptr);

    void run();

    TcpClientSocket* getClient();

    //~clientThread();

private slots:
    //在发出信号之后回收线程和该线程中的客户端套接字
    void thread_slot_disconnect(long long int);

    //处理连接数据库
    void thread_slot_connectDB();

    //线程中接收到登录请求
    //void thread_slot_received_loginRequest(int userID);

    void handleRequest(QString& request);

signals:
    //线程中收到信息
    void thread_signal_received(QString& data, long long int descriptor);

    //线程中收到断连信号
    void thread_signal_disconnected(long long int descriptor);

    //线程中接收到登录初始化请求
    void thread_signal_received_loginRequest(int userID, long long int descriptor);

    //线程中接收到刷新请求
    void thread_signal_received_refreshRequest(long long descriptor);

    //线程中接受到刷新子帖请求
    void thread_signal_received_refreshSonPostRequest(long long descriptor);

    void thread_signal_received_debug(const QString& msg);

private:
    TcpClientSocket* client;
};

#endif // CLIENTTHREAD_H
