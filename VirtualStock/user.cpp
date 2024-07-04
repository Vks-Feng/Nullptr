#include "user.h"

//默认构造函数
User::User(){
    ID = 1;
    name = "vks";
    password = "123";
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

int User::GetBalance(){
    return virtualcurrency.GetValue();
}

int User::GetRanking(){
    return ranking;
}
