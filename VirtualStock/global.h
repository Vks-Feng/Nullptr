#ifndef GLOBAL_H
#define GLOBAL_H

#include "usermanage.h"

class Global
{
public:
    static Global& instance() {
        static Global _instance;
        return _instance;
    }

    UserManage* getGlobalUserManage() const { return um; }
    void setGlobalVar(UserManage* _um) { um = _um; }

private:
    Global() : um(nullptr) {}
    UserManage* um;
};

#endif // GLOBAL_H
