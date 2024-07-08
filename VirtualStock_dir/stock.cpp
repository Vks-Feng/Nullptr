#include "stock.h"
#include <QStringList>

//---------------股票类Stock-----------------
//构造函数和接口，接口返回private成员即可
Stock::Stock(double _price,int _companyId,long _volume, int _year, int _month){
    singlePrice = _price;
    companyId = _companyId;
    volume = _volume;
    year = _year;
    month = _month;

    QStringList company_names = {
        "AAPL", "AMZN", "GOOGL", "IBM", "INTC",
        "JBLU", "META", "MSFT", "TSLA"
    };

    QString company_name;

    if (_companyId >= 1 && _companyId <= company_names.size()) {
        companyName = company_names[_companyId - 1];
    } else {
        companyName = "Unknown";
    }

}

Stock::Stock()
{
    singlePrice=100.0;
    companyId=12;
    volume=199;
    year=2004;
    month=12;
}

double Stock:: GetSinglePrice()const{
    return singlePrice;
}

int Stock:: GetCompanyId(){
    return companyId;
}

long Stock:: GetVolumn(){
    return volume;
}

int Stock:: GetYear(){
    return year;
}

int Stock::GetMonth(){
    return month;
}

QString Stock::GetCompanyName(){
    return companyName;
}

// std::map<int,double> Stock::GetStockMap(){
//     return this->stockMap;
// }
