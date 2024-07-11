#pragma once

#include <stdio.h>
#include <mysql.h>
#include <iostream>
#include <QString>

#include <user.h>
#include <record.h>
#include <portfolio.h>
#include <QRandomGenerator>
#include <post.h>

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

    //----------Tools---------
    //输入公司id，返回公司名
     QString Id2Name(int id);
    //----------Tools---------



    //----------Basic Operations---------

    //Usually you use this default constructor instead of using the constructor directorly
    BackDB();

    //Input the formal query lines that can be used in MySql
    //and return a MYSQL_RES object
    //Won't show the result of the query
    MYSQL_RES* query(const char* query);
    MYSQL_RES* query(QString query);

    //Show the query result of the query
    //And return the result as QStirng
    void showQuery(const char* query);
    void showQuery(QString qStr);

    //获取某个表格的成员描述
    void tableDesc(const char* tableName);

    //Close the Mysql
    void close();

    //----------Basic Operations---------



    //----------User---------

    //vks--将返回值修改为int，创建失败返回-1，创建成功返回userID
    int addUser(QString name, QString password);

    //查找用户名为name的数据
    //查找到的数据条数不为0则返回true，表示存在
    //查找到的数据条数为0则返回false，表示不存在
    bool isExist(QString name);

    //查找用户id是否存在
    bool TotalValueIsExist(int User_id);

    //根据用户名查找对应的密码，判断密码是否正确
    //正确则返回true，错误返回false
    bool isPasswordEqual(QString name, QString password);

    //根据用户名查找数据，并根据数据构建User，返回一个User
    User enableUser(QString name);

    //传入id，价格totalPrice,在user表中balance上减去该数值
    void declineBalance(int id, int totalPrice);

    //传入id，价格totalPrice,在user表中balance上加去该数值
    void inclineBalance(int id, int totalPrice);

    //返回用户余额
    int GetBalance(int user_id);

    //返回当前所有用户数量
    int CountUser();

    void setTime(int _useId,int montha);
    int getTime(int _userId);

    void setIntroduction(int _userId, QString _content);
    void setRanking(int _userId, int _ranking);

    QString getIntroduction(int _userId);//获取用户的个性签名,总资产得新建个表了
    void setTotalvalue(int user_ID,int value);//设置用户的总资产
    int getTotalvalue(int userid);//读取总资产
    //需求：：每个用户读取排行榜需要读取所有人的总资产

//    排行榜需求
//        需要在本机获取所有用户的用户名
    std::vector<QString> getAllUserName();//返回一个数组存储所有的用户名

    //根据用户名把id返回出来,如果未找到，返回-1
    int getUserId(QString name);


    //----------User---------



    //----------Portfolios---------

    //给portfolios表中添加成员
    void addPortfolios(int user_id,int company_id,int volume);

    //每当切换SellOutStockBox的时候调用查询函数，传递参数用户id，股票id
    //在portfolios中查询id对应股票的余量
    //看你数据库的设计我默认为用户买入的时候才会添加portfolios数据，没买就不添加

    //所以：
    //若找到,返回余量，若没找到，返回-1(这里有一个bug，如果是0会新建，这里解决了)
    int getUserVolume(int userID, int companyID);


    //传入用户id，股票id，购买数量，在portfolio中添加股票对应数量
    //若该用户id有对应id的股票，则在volumn字段上添加该数量
    //若该用户id无对应id的股票，则在新建一条数据添加到表中

    void AddStock(int userID, int stockID, int volumn);

    //给传入一个用户id，查询portfolio表中该用户id对应的数据，并且构建一个根据这些数据构建好的Portfolio
    Portfolio& getUserPortfolio(int userID);

    //传入用户id，股票id，卖出数量，在portfolio中添加股票减去数量
    //若该用户id有对应id的股票，则在volumn字段上减去该数量
    //若该用户id无对应id的股票，则不操作即可
    void RemoveStock(int userID, int company_id, int volume);

    //----------Portfolios---------



    //----------Record---------

    //给record表中添加成员
    void addRecord(int _user_id, Record _record);

    //传入一个用户id，查询Record表中的数据，并根据这些数据构建一个Record的数组，并返回
    std::vector<Record>& getUserRecord(int userID);

    //----------Record---------



    //----------Stock---------

    //每当切换BuyInStockBox的时候调用查询函数，传递参数为股票的companyId,年份，月份
    //找到对应的股票
    //返回一个长度为2的vector数组的引用，第一个为数字为股票价格,第二个数字为股票容量
    std::vector<long>& getStockInfo(int id, int year, int month);

    //----------Stock---------



    //----------Forum---------
    void addPost(Post post);//写入到Forum表格
    std::vector<Post>  getforum();//获取所有post，形成一个vector<Post>
    //----------Forum---------



    //----------News---------
    //传入月份，查询从一月到传入月份为止的所有新闻；构建一个数组
    //传出以月份为key,news数组的map
    std::map<int, std::vector<QString>> &getNews(int _month);
    //----------News---------



    //----------comments-table---------
    void setComment(int user_id,QString _comment);
    //----------comments-table---------



    //----------test---------
    void test();
    void testEnableUser();
    void testIsPasswordEqual();
    void testUserAdd();
    void testGetStockInfo();
    void testBalance();
    void testGetUserVolume();
    void testAddStock();
    void testGetBalance();
    void testGetUserRecord();
    void testGetUserPortfolio();
    void testAddPost();
    void testGetForum();
    void testGetNews();
    void testRecord();
    void testPortfolios();
    //----------test---------
};

