#include "user.h"
#include<QString>

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

VirtualCurrency GetVIr(){

};//Pass

int User::GetRanking(){
    return ranking;
}
