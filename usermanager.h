#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "user.h"
#include "databasemanager.h"
#include "includes.h"

class UserManager
{
public:
    static UserManager& instance() {
            static UserManager instance;
            return instance;
        }
    bool createUser(const QString& login, const QString& password, const QString& role);
    int loginUser(const QString& login, const QString& password);
    QString getCurrentUserLogin();
    QString getCurrentUserRole();
    QString setCurrentUserRole(const QString& role);
    QString setCurrentUserLogin(const QString& login);

private:
    DatabaseManager databaseManager;
    UserManager() {}
    QString hashPassword(const QString& password);
    QString currentUserLogin_;
    QString currentUserRole_;
};

#endif // USERMANAGER_H
