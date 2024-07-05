#ifndef USER_H
#define USER_H
#include<QString>
#include<string>
#include<map>
#include<vector>

#include"virtualcurrency.h"
#include"record.h"
#include"portfolio.h"

using namespace std;

class User{
private:
    int ID;
    QString name;
    QString password;
    VirtualCurrency virtualcurrency;
    Portfolio portfolio;
    vector<Record> r;
    int ranking;

public:
    //构造函数
    User();
    User(QString _name,QString _password){
        name = _name;
        password = _password;
    }

    User(int id, QString userName,QString password,
         int balance,int ranking);
    //Return the coresponding data member

    int GetId();

    QString GetName();

    QString GetPassword();

    vector<Record> GetRecord();

    void AddRecord(Record _r);

    Portfolio GetPortfolio();

    VirtualCurrency GetVir();//Pass

    int GetBalance();

    int GetRanking();//获取排行

};

#endif // USER_H
