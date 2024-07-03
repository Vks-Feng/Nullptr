#include "virtualcurrency.h"

VirtualCurrency::VirtualCurrency()
{
    value = 64800;
}

//存款
bool VirtualCurrency::deposit(double amount){
    if(amount > 0)
    {
        value += amount;
        return true;

    }else{
        return false;
    }
}

//取款
bool VirtualCurrency::withdraw(double amount){
    if(amount > 0 && value >= amount){
        value -= amount;
        return true;
    }else{
        return false;
    }
}

//了解资产
int VirtualCurrency::GetValue(){
    return value;
}
