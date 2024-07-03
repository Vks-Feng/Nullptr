#ifndef PORTFOLIO_H
#define PORTFOLIO_H
#include<QString>
#include<string>
#include<map>
#include"stock.h"
using namespace std;

//投资管理类
class Portfolio {

private:
    std::map<int, int> holdings; // Map of stock symbol to quantity
    //即第一个int(key)代表公司/股票id，第二个代表持有数量(键值对）

public:
    Portfolio();

    Portfolio(const std::map<int,int>& initialHoldings);

    void addStock(Stock& stock, int quantity);//根据key,添加指定quantity的股票到holdings

    void removeStock(Stock& stock, int quantity);//移除指定quantity的股票到holdings

    std::map<int, int> getHoldings();//获取当前持仓的股票及数量映射

    double getTotalValue();//计算组合股票的总价值（根据每只股票的单价和持有量计算总值）

};

#endif // PORTFOLIO_H
