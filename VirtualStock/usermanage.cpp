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

int UserManage::Check(QString name, QString password){
    //检查输入的用户名还有密码是否已经具有
    //0：用户不存在，1：账号或密码错误，2： 成功登录
    //0时询问是否创建，调用Create()
    for(auto& user: users){
        if(user.GetName() == name && user.GetPassword() == password){
            return 2; //Success
        }else if(user.GetName() == name || user.GetPassword() == password){
            return 1;
        }
    }
    return 0;//用户不存在
}

void UserManage::Login(QString name, QString password){
    //用户登录
    int loginResult = Check(name,password);
    //调用Check，如果返回是0，调用Create()；其他情况进行提示
    if(loginResult == 0){
        Create(name,password);
    }else if(loginResult == 1){
        //提示"密码或账号错误！"
    }else{
        //登陆成功
    }
}

void UserManage::Create(QString name, QString password){
    //用户创建
    User newUser(name,password);
    UserAdd(newUser);
}

int UserManage::GetSize(){
    //返回size，即用户总数
    return size;
}

UserManage::~UserManage(){
    //析构函数
}

