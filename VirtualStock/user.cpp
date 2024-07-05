#include "user.h"

//默认构造函数
User::User(){
    ID = 1;
    name = "vks";
    password = "123";
}

User::User(int _id,QString  _userName,QString _password,int _balance,int _ranking)
{
    ID=_id;
    name=_userName;
    password=_password;
    ranking=_ranking;
    this->virtualcurrency.SetValue(_balance);
}

//Return the coresponding data member
int User::GetId(){
    return ID;
}

QString User::GetName(){
    return name;
}

QString User::GetPassword(){
    return password;
}

vector<Record> User::GetRecord(){
    return r;
}

VirtualCurrency User::GetVir(){
    return virtualcurrency;
};

void User::AddRecord(Record _r){
    r.push_back(_r);
}

Portfolio User::GetPortfolio(){
    return portfolio;
}

int User::GetBalance(){
    return virtualcurrency.GetValue();
}

int User::GetRanking(){
    return ranking;
}
