#include "record.h"

Record::Record(QString _date, Stock _s, long _volume, bool _tradetype, long _totalprice){
    date = _date;
    s = _s;
    volume = _volume;
    tradetype = _tradetype;
    totalprice = _totalprice;
}

Record::Record(){
    date = "2020-07";
    s = Stock();
    volume = 0;
    tradetype = true;
    totalprice = 100;
}

//------------------记录Record-------------
//均为接口，接口返回private成员即可
QString Record::GetDate(){
    return date;
}

Stock Record::GetStock(){
    return Record::s;
}

long Record::GetVolume(){
    return Record::volume;
}

long Record::GetTradeType(){
    return Record::tradetype;
}

long Record::GetTotalPrice(){
    return Record::totalprice;
}
