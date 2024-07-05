#include "usermanage.h"
using namespace std;

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
    QString dataBaseName = "vks";
    QString dataBasePassword = "123";
    if(dataBaseName == name && dataBasePassword == password){
        return 2; //Success
    }else if(dataBaseName == name || dataBasePassword == password){
        return 1;//账号或密码错误
    }
    return 0;//用户不存在
}

bool UserManage::Create(QString name, QString password){
    //用户创建
//---------真实代码--------
//    if(Check(name, password) == 0) {
//        //去数据库写入数据
//        return true;
//    }else{
//        return false;
//    }
//------------------------
    return true;
}

int UserManage::GetSize(){
    //返回size，即用户总数
    return size;
}

UserManage::~UserManage(){
    //析构函数
}

