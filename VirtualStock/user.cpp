#include "user.h"

//默认构造函数
User::User(){
    ID = 1;
    name = "vks";
    password = "123";
    virtualcurrency = VirtualCurrency();
    portfolio = Portfolio();
    r = std::vector<Record>();
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
};//Pass

int User::GetRanking(){
    return ranking;
}

void User::AddRecord(Record _r){
    r.push_back(_r);
}

Portfolio User::GetPortfolio(){
    return portfolio;
}
