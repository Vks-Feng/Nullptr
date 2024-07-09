#include "user.h"

//默认构造函数
User::User(){
    ID = 1;
    name = "vks";
    password = "123";
    currentdate=Date(2023,12);
}

User::User(int _id,QString  _userName,QString _password,int _balance,int _ranking)
{
    ID=_id;
    name=_userName;
    password=_password;
    ranking=_ranking;
    this->virtualcurrency.SetValue(_balance);
    currentdate=Date(2023,12);
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

std::vector<Record> User::GetRecord(){
    return r;
}

VirtualCurrency User::GetVir(){
    return virtualcurrency;
};

void User::AddRecord(Record _r){
    r.push_back(_r);
}

Portfolio* User::GetPortfolio(){
    return &portfolio;
}

int User::GetBalance(){
    return virtualcurrency.GetValue();
}

int User::GetRanking(){
    return ranking;
}
Date* User::GetDate(){
    return &currentdate;
}

