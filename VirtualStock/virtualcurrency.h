#ifndef VIRTUALCURRENCY_H
#define VIRTUALCURRENCY_H
#include<QString>
#include<string>
#include<map>
//using namespace std;

//用户虚拟资产
class VirtualCurrency{
private:
    int value=64800;//豪气不，一上来就给你100个648

public:
    //构造函数
    VirtualCurrency();

    VirtualCurrency(int _value);

    //存款
    bool deposit(double amount);

    //取款
    bool withdraw(double amount);

    //设置金钱
    void SetValue(int _value);

    //了解资产值
    int GetValue();
};

#endif // VIRTUALCURRENCY_H
