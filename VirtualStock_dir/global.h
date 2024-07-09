#ifndef GLOBAL_H
#define GLOBAL_H

#include "usermanage.h"
#include "backdb.h"
#include "clientsocket.h"

class Global
{
public:
    static Global& instance() {
        static Global _instance;
        return _instance;
    }

    UserManage* getGlobalUserManage() const { return um; }
    void setGlobalUserManage(UserManage* _um) { um = _um; }
    BackDB* getGlobalDataBase() const { return db; }
    void setGlobalDataBase(BackDB* _db) { db = _db; }
    ClientSocket* getGlobalClient() { return client; }
    void setGlobalClient(ClientSocket* _client) { client = _client; }
    void setGlobalYear(int _year) { Year = _year; }
    int getYear() { return Year; }

private:
    Global() : um(nullptr) {}
    UserManage* um;
    BackDB* db;
    ClientSocket* client;
    int Year = 2023;
};

#endif // GLOBAL_H
