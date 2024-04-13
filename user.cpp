#include "user.h"

User::User(const QString& login, const QString& password, const QString& role)
    : login_(login), password_(password), role_(role)
{}

QString User::getLogin () const
{
    return login_;
}

QString User::getPassword() const
{
    return password_;
}

QString User::getRole() const
{
    return role_;
}
