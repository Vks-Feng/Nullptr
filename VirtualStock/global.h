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

private:
    Global() : um(nullptr) {}
    UserManage* um;
    BackDB* db;
};

#endif // GLOBAL_H
