#include "tcpserver.h"
#include "ui_tcpserver.h"

TcpServer::TcpServer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TcpServer)
{
    ui->setupUi(this);
    ui->onlineClientStatus->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->onlineClientStatus->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    connect(ui->StartServer, &QPushButton::clicked, this, &TcpServer::createServer);
    connect(ui->sendMessageButton, &QPushButton::clicked, this, &TcpServer::sendMessage);
}

TcpServer::~TcpServer()
{
    delete ui;
}

void TcpServer::createServer(){

    server = new Server(this, 12345);
    if(server->listen(server->ipAddress, server->port)){
        showDebugMessage("listenning!!!");
        qDebug() << "listenning!!!";
    }else{
        showDebugMessage("can not listen");
    }
    if (serverStatus) {
        ui->serverInfoList->addItem("Server is already started");
        return;
    }

    if (!server) {
        qDebug() << "Failed to create server!";
        ui->serverInfoList->addItem("Failed to start server");
        return;
    }

    qDebug() << "Server Start!";
    qDebug() << "Listening at port:" << server->port;
    ui->serverInfoList->addItem(QString("Server start! Listening at port: %1").arg(server->port));

    // 连接信号和槽
    connect(server, &Server::signal_ClientConnected, this, &TcpServer::handleConnectedMessage);
    connect(server, &Server::signal_ClientConnected, this, &TcpServer::updateCurrentClientNum);
    connect(server, &Server::signal_ReceiveMessage, this, &TcpServer::handleReceivedMessage);
    connect(server, &Server::signal_ClientDisconnected, this, &TcpServer::handleDisconnectedMessage);
    connect(server, &Server::signal_ClientDisconnected, this, &TcpServer::updateCurrentClientNum);
    connect(server, &Server::signal_showDebugMessage, this, &TcpServer::showDebugMessage);
    serverStatus = true;
}

void TcpServer::Notification(QString notice){
    QMessageBox msgBox;
    msgBox.setText(notice);
    msgBox.exec();
}

void TcpServer::sendMessage(){
    if(serverStatus){
        if(ui->sendToClientMessage->toPlainText().isEmpty()){
            Notification("输入不能为空");
            return;
        }
        QString msg = ui->sendToClientMessage->toPlainText();
        int descriptor = ui->descriptorInput->text().toInt();
        if(server != nullptr){
            server->sendMessageToClients(msg, descriptor);
        }
    }else{
        Notification("服务器未启动");
    }
}

void TcpServer::handleConnectedMessage(QString& clientConnectedInfo, long long int descriptor){
    QString time = QDateTime::currentDateTime().toString();
    QString showContent = time + " -- " + clientConnectedInfo;
    ui->serverInfoList->addItem(showContent);
    addOnlineClient(descriptor);
}

void TcpServer::handleDisconnectedMessage(QString& clientDisconnectedInfo, long long int descriptor){
    QString time = QDateTime::currentDateTime().toString();
    QString showContent = time + " -- " + clientDisconnectedInfo;
    ui->serverInfoList->addItem(showContent);
    removeOnlineClient(descriptor);
}

void TcpServer::handleReceivedMessage(QString& msg, long long int descriptor){
    QString clientInfo = server->getClientInfo(descriptor);
    QString time = QDateTime::currentDateTime().toString();
    QString showContent = time + " -- " + clientInfo + ":  " + msg;
    ui->serverInfoList->addItem(showContent);
}

void TcpServer::addOnlineClient(long long int descriptor){
    QString IP = server->getClientIP(descriptor);
    quint16 Port = server->getClientPort(descriptor);
    QString status = "online";
    int rowCount = ui->onlineClientStatus->rowCount();
    QTableWidgetItem* iIP = new QTableWidgetItem(IP);
    QTableWidgetItem* iPort = new QTableWidgetItem(QString::number(Port));
    QTableWidgetItem* idescriptor = new QTableWidgetItem(QString::number(descriptor));
    QTableWidgetItem* istatus = new QTableWidgetItem(status);
    ui->onlineClientStatus->setRowCount(ui->onlineClientStatus->rowCount()+1);
    ui->onlineClientStatus->setItem(rowCount, 0, iIP);
    ui->onlineClientStatus->setItem(rowCount, 1, iPort);
    ui->onlineClientStatus->setItem(rowCount, 2, idescriptor);
    ui->onlineClientStatus->setItem(rowCount, 3, istatus);
}

void TcpServer::removeOnlineClient(long long int descriptor){
    int maxRow = ui->onlineClientStatus->rowCount();
    for(int i = 0; i < maxRow; i++){
        QTableWidgetItem* item = ui->onlineClientStatus->item(i, 2);
        qDebug() << item->text() << " and " << descriptor;
        if(item->text() == QString::number(descriptor)){
            //ui->onlineClientStatus->removeRow(i);
            QString status = "offline";
            QTableWidgetItem* istatus = new QTableWidgetItem(status);
            ui->onlineClientStatus->setItem(i, 3, istatus);
            qDebug() << i << "delete";
            showDebugMessage(QString("%1 was removed").arg(descriptor));
        }
    }
}

void TcpServer::updateCurrentClientNum(){
    if(server != nullptr){
        ui->currentClientNum->setText(QString::number(server->tcpclientsocketlist.size()));
    }else{
        ui->currentClientNum->setText("-1");
    }
}

void TcpServer::showDebugMessage(const QString& msg){
    QString time = QDateTime::currentDateTime().toString();
    QString showContent = time + " -- " + ":  " + msg;
    ui->serverInfoList->addItem(showContent);
}




