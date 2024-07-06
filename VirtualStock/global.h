#ifndef GLOBAL_H
#define GLOBAL_H

#include "usermanage.h"
#include "backdb.h"

class Global
{
public:
    static Global& instance() {
        static Global _instance;
        return _instance;
    }

    UserManage* getGlobalUserManage() const { return um; }
    void setGlobalVar(UserManage* _um) { um = _um; }
    BackDB* getClobalDataBase() const { return db; }
    void setGlobalDataBase(BackDB* _db) { db = _db; }
    void setGlobalDate(int _year, int _month) { Year = _year; Month = _month; }
    int getYear() { return Year; }
    int getMonth() { return Month; }

private:
    Global() : um(nullptr) {}
    UserManage* um;
    BackDB* db;
    int Year = 2023;
    int Month = 12;
};

#endif // GLOBAL_H
