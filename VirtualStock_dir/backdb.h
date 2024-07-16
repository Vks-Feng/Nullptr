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
#include <QCryptographicHash>
#include <QVector>

class BackDB
{
private:
    MYSQL mysql;//The MySql object

    const char* host; // MySQL server host 地址（阿里云中为公网地址）
    const char* user; // MySQL username
    const char* password; // MySQL password
    const char* database; // MySQL database name
    unsigned int port = 3306; // MySQL port (default is 3306)
    const char* unix_socket = nullptr; // Unix socket (can be nullptr for TCP/IP)
    unsigned long client_flag = 0; // Connection flags (usually 0)

public:
    //----------Consturctor----------
    BackDB(const char* _host, const  char* _user, const  char* _password, const  char* _database,
           unsigned int _port = 3306, const char* _unix_socket = nullptr, unsigned long _client_flag = 0);
    //----------Consturctor----------



    //----------Tools---------
    //输入公司id，返回公司名(对应数据表中的公司名称缩写)(1-8)
    QString Id2Name(int id);

    QString generateHash(const QString& input);
    //----------Tools---------



    //----------Basic Operations---------

    //执行查询操作，返回结果集
    MYSQL_RES* query(const char* query);
    MYSQL_RES* query(QString query);

    //展示从数据库查询返回的结果
    void showQuery(const char* query);
    void showQuery(QString qStr);

    //获取某个表格的列描述
    void tableDesc(const char* tableName);

    //关闭数据库
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

    //返回用户活动资产
    int GetBalance(int user_id);

    //返回当前所有用户数量
    int CountUser();

    //设置用户时间
    void setTime(int _useId,int montha);
    //获取用户时间
    int getTime(int _userId);

    //设置介绍说明
    void setIntroduction(int _userId, QString _content);
    //获取自我介绍
    QString getIntroduction(int _userId);//获取用户的个性签名,总资产得新建个表了
    //设置排行
    void setRanking(int _userId, int _ranking);


    //设置用户的总资产
    void setTotalvalue(int user_ID,int value);
    //读取总资产
    int getTotalvalue(int userid);
    //需求：：每个用户读取排行榜需要读取所有人的总资产

//    排行榜需求
//    需要在本机获取所有用户的用户名
    std::vector<QString> getAllUserName();//返回一个数组存储所有的用户名

    //根据用户名把id返回出来,如果未找到，返回-1
    int getUserId(QString name);


    //----------User---------



    //----------Portfolios---------

    //给portfolios表中添加成员
    void addPortfolios(int user_id,int company_id,int volume);

    //寻找该用户对应的股票雨量,返回余量，若没找到，返回-1(这里有一个bug，如果是0会新建，这里解决了)
    int getUserVolume(int userID, int companyID);

    //传入用户id，股票id，购买数量，在portfolio中添加股票对应数量
    //若该用户id有对应id的股票记录(包括记录为0的情况)，则在volumn字段上添加该数量
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
    //写入到Forum表格
    void addPost(Post post);

    //获取所有post，形成一个vector<Post>
    std::vector<Post>  getforum();
    //----------Forum---------



    //----------News---------
    //传入月份，查询从一月到传入月份为止的所有新闻；构建一个数组
    //传出以月份为key,news数组的map
    std::map<int, std::vector<QString>> &getNews(int _month);
    //----------News---------



    //----------comments-table---------
    void setComment(int user_id,QString _comment);
    //----------comments-table---------



    //----------KLines----------
    // 从2022（之后绘图都从这个日期开始）,返还给我这段日期中每个时间点对应的四个数:open,close,lowest,highest
    QVector<QVector<double>> getRawDatas(int company_id,int time);

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
    BackDB();
};

