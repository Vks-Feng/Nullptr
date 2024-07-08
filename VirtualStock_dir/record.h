#ifndef RECORD_H
#define RECORD_H
#include<QString>
#include<string>
#include<map>
#include"stock.h"
//using namespace std;

class Record{
private:
    QString date;//用“YYYY-MM"形式进行存储
    int company_id;//具体到哪一只股票‘
    long volume;//该笔交易容量
    bool tradetype;//交易类型（买入1/卖出0)
    long totalprice;
public:
    Record(QString _date, int _company_id, long _volume, bool _tradetype, long _totalprice);

    Record();

    //理论来说记录在交易完成时创建，不能修改交易记录，但是能获取交易信息
    QString GetDate();

    int GetCompanyId();

    long GetVolume();

    bool GetTradeType();

    long GetTotalPrice();
};

#endif // RECORD_H
