#ifndef USERMANAGE_H
#define USERMANAGE_H
#include<QString>
#include<string>
#include<map>
#include<vector>

#include "portfolio.h"
#include"user.h"

//用户管理类
class UserManage{

private:

    vector<User> users;//存储用户实例
    Portfolio plan; //应该要等到后面实现，version1先不管了先
    int size;//存放用户个数


public:
    //初始函数
    UserManage();

    //添加用户,记得size++
    bool UserAdd(User _user);

    //检查输入的用户名还有密码是否已经具有
    int Check(QString name, QString password);
    //0：用户不存在，1：账号或密码错误，2： 成功登录
    //0时询问是否创建，调用Create()

    //用户登录
    void Login(QString name, QString password);
    //调用Check，如果返回是0，调用Create()；其他情况进行提示

    //用户创建
    void Create(QString name, QString password);
    //调用Check，如果返回是0，直接创建用户；其他情况进行提示

    int GetSize();
    //返回size

    //销毁函数
    ~UserManage();
};

#endif // USERMANAGE_H
