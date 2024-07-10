#ifndef PORTFOLIO_H
#define PORTFOLIO_H
#include<QString>
#include<string>
#include<map>
#include"stock.h"
//using namespace std;

//投资管理类
class Portfolio {

private:
    std::map<int, int> holdings; // Map of stock symbol to quantity
    //即第一个int(key)代表公司/股票id，第二个代表持有数量(键值对）

public:
    Portfolio();

    Portfolio(const std::map<int,int>& initialHoldings);

    void addStock(int stock, int quantity);//根据key,添加指定quantity的股票到holdings

    void removeStock(int stock, int quantity);//移除指定quantity的股票到holdings

    int getHoldings(int key);//获取当前持仓的股票及数量映射

    std::map<int, int> getTotalValue();//为了避免重复包含，这里直接把map，也就是存储companyID和对应持有量return,计算去外面算

};

#endif // PORTFOLIO_H
