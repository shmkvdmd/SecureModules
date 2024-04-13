#include "usermanager.h"
#include <QCryptographicHash>
#include "user.h"
bool UserManager::createUser(const QString& login, const QString& password, const QString& role) {
    QString hashedPassword = hashPassword(password);
    User newUser(login, password, role);
    return databaseManager.createUser(newUser, hashedPassword);
}

int UserManager::loginUser(const QString& login, const QString& password) {
    QString hashedPassword = hashPassword(password);
    if (databaseManager.doesUserExist(login, hashedPassword))
        {
            currentUserRole_ = databaseManager.getUserRole(login, hashedPassword);
            currentUserLogin_ = login;
            if(currentUserRole_ == "Администратор"){
                return 777;
            }
            return 1;
        }
        return 0;
}

QString UserManager::hashPassword(const QString& password) {
    QByteArray hash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    return QString(hash.toHex());
}

QString UserManager::getCurrentUserLogin()
{
    return currentUserLogin_;
}

QString UserManager::getCurrentUserRole()
{
    return currentUserRole_;
}
