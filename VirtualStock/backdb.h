#pragma once

#include <stdio.h>
#include <mysql.h>
#include <iostream>
#include <QString>

#include <user.h>
#include <record.h>
#include <portfolio.h>
#include <QRandomGenerator>

class BackDB
{
private:
    MYSQL mysql;//The MySql object

    const char* host = "10.128.11.30"; // MySQL server host ("Under XiaoMi13 is 192.168.237.55") Don't change it!!!
    const char* user = "visitor"; // MySQL username
    const char* password = "VirtualStokes"; // MySQL password
    const char* database = "stokes"; // MySQL database name
    unsigned int port = 3306; // MySQL port (default is 3306)
    const char* unix_socket = nullptr; // Unix socket (can be nullptr for TCP/IP)
    unsigned long client_flag = 0; // Connection flags (usually 0)

    //Constructor , the basic information is host+user+password+database
    BackDB(const char* _host, const  char* _user, const  char* _password, const  char* _database,
           unsigned int _port = 3306, const char* _unix_socket = nullptr, unsigned long _client_flag = 0);



public:

    //Usually you use this default constructor instead of using the constructor directorly
    BackDB();

    //Input the formal query lines that can be used in MySql
    //and return a MYSQL_RES object
    //Won't show the result of the query
    MYSQL_RES* query(const char* query);

    MYSQL_RES* query(QString query);

    //Show the query result of the query
    //And return the result as QStirng
    QString showQuery(const char* query);
    QString showQuery(QString qStr);

    //Add a user into the users table
    void addUser(User _user);
    void testUserAdd();

    //Add a Porfolios into the portfolios table
    void addPortfolios(int user_id,int company_id,int volume);
    void testPortfolios();

    //Add a record into the trade record table;
    void addRecord(int _user_id, Record _record);
    void testRecord();

    //Get the information about the field
    void tableDesc(const char* tableName);

    //Close the Mysql
    void close();

    //登录流程：
    //1.用户输入用户名、密码，点击登录后调用Login(string name, string password)

    //2.Login 调用check函数，首先查找表中用户名是否存在
    //若存在，调用isPasswordEqual(name，password)函数判断，密码是否正确（isequal内部获取数据库中的密码来判断）
    //若正确，返回登录的信号
    //执行enableUser(),用数据库中该用户的数据实例化一个user对象，并返回
    //若错误，返回密码错误的代号
    //若不存在，返回用户名不存在的信号


    //注册流程：
    //1.用户输入用户名，密码，点击后调用Register(string name, string password)

    //2.在数据库中查询用户名是否存在isExist(string name)
    //若存在返回用户名存在的信号
    //若不存在，addUser(string name, string password)，同时在数据库中添加用户信息

    //具体需要的接口如下：

    //查找用户名为name的数据
    //查找到的数据条数不为0则返回true，表示存在
    //查找到的数据条数为0则返回false，表示不存在
        bool isExist(QString name);

    //    //根据传入参数在数据库中添加新数据
    //    //成功添加则返回true，否则返回false（避免用户名存在）
        bool addUser(QString name, QString password);

    //    //根据用户名查找对应的密码，判断密码是否正确
    //    //正确则返回true，错误返回false
        bool isPasswordEqual(QString name, QString password);


    //    //根据用户名查找数据，并根据数据构建User，返回一个User
        User enableUser(QString name);




        void testIsPasswordEqual();
        void testEnableUser();
};
