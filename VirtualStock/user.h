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
    //Return the coresponding data member
    int GetId();

    QString GetName();

    QString GetPassword();

    vector<Record> GetRecord();

    VirtualCurrency GetVIr();//Pass

    int GetBalance();

    int GetRanking();//获取排行

};

#endif // USER_H
