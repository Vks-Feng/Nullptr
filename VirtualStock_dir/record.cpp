#include "record.h"


Record::Record(QString _date, int _company_id, long _volume, bool _tradetype, long _totalprice)
{
    date = _date;
    company_id=_company_id;
    volume = _volume;
    tradetype = _tradetype;
    totalprice = _totalprice;
}

Record::Record(){
    date = "2020-07";
    company_id=1;
    volume = 0;
    tradetype = 1;
    totalprice = 100;
}

//------------------记录Record-------------
//均为接口，接口返回private成员即可
QString Record::GetDate(){
    return date;
}

int Record::GetCompanyId()
{
    return company_id;
}


long Record::GetVolume(){
    return volume;
}

bool Record::GetTradeType(){
    return tradetype;
}

long Record::GetTotalPrice(){
    return totalprice;
}
