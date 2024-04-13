#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    User(const QString& login, const QString& password, const QString& role);

    QString getLogin() const;
    QString getPassword() const;
    QString getRole() const;

private:
    QString login_;
    QString password_;
    QString role_;
};

#endif // USER_H
