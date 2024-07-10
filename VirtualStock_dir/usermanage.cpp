#include "usermanage.h"
#include "global.h"
//using namespace std;

//---------------------用户管理类UserManage------------------------
UserManage::UserManage(){
    //UserManage构造函数
    size = 0;
}

bool UserManage::UserAdd(User _user){
    //添加用户
    users.push_back(_user);
    size++;
    return true;
}

User* UserManage::GetUser(int i){
    return &users[i];
}

int UserManage::Check(QString name, QString password){
    //检查输入的用户名还有密码是否已经具有
    //0：用户不存在，1：账号或密码错误，2： 成功登录
    //0时询问是否创建，调用Create()
//    QString dataBaseName = "vks";
//    QString dataBasePassword = "123";
//    if(dataBaseName == name && dataBasePassword == password){
//        return 2; //Success
//    }else if(dataBaseName == name || dataBasePassword == password){
//        return 1;//账号或密码错误
//    }
//    return 0;//用户不存在
    if(Global::instance().getGlobalDataBase()->isExist(name)){
        if(Global::instance().getGlobalDataBase()->isPasswordEqual(name, password)){
            return 2;
        } else {
            return 1;
        }
    } else {
        return 0;
    }
}

int UserManage::Create(QString name, QString password){
    if(Global::instance().getGlobalDataBase()->isExist(name)){
        return -1;
    } else {
        int userID = Global::instance().getGlobalDataBase()->addUser(name, password);
        return userID;
    }
}

int UserManage::GetSize(){
    //返回size，即用户总数
    return size;
}

void UserManage::updateUser(int id){
    QString name = users[id].GetName();
    users[id] = Global::instance().getGlobalDataBase()->enableUser(name);
}

UserManage::~UserManage(){
    //析构函数
}

