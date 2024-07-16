#include "portfolio.h"

//---------------------投资管理类Portfolio------------------------
Portfolio::Portfolio()
{
 //默认空映射
}


Portfolio::Portfolio(const std::map<int,int>& initialHoldings):holdings(initialHoldings){

    //已有映射构造函数
}

void Portfolio::addStock(int stock, int quantity){
    //功能待实现
    //用户买入该股票，并且进入用户名下

    //查找是否已经持有该股
    auto it = holdings.find(stock);
    if(it != holdings.end()){
        //已有，增加数量
        it->second +=quantity;
    }else{
        //未持有，增加键值对记录
        holdings[stock] = quantity;
    }

}

void Portfolio::removeStock(int stock, int quantity){
    //功能待实现
    //用户卖出股票，名下股票相应删去

    //查找是否已经持有该股
    auto it = holdings.find(stock);
    if(it != holdings.end()){
        //持有仓；并且持有数量大于要移除的数量
        if(it->second >= quantity){
            it->second -= quantity;
            if(it->second <= 0)
                holdings.erase(it);
        }else{
            //要移除的数量大于总量
            //抛出错误
            throw std::runtime_error("Trying to remove more stocks than owned.");
        }
    }
}

int Portfolio::getHoldings(int key){
    return this->holdings[key];
}

std::map<int,int> Portfolio::getTotalValue(){
    //为了避免重复包含，这里直接把map，也就是存储companyID和对应持有量return,计算去外面算
    return holdings;

}
