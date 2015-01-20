#include "models/user.h"
#include "database/userdatabase.h"


User::User()
{

}

User::User(int id)
{
    _id = id;
    hydrat(id);
}



void User::commit() {
    UserDatabase::instance()->updateUser(*this);
}

void User::remove()
{
    // Not use
}

void User::hydrat(int id)
{
    User* user = UserDatabase::instance()->getUser(id);
    _id = id;
    _firstname = user->getFirstname();
    _lastname = user->getLastname();
    _company = user->getCompany();
    _title = user->getTitle();
    _address = user->getAddress();
    _postalCode = user->getPostalCode();
    _city = user->getCity();
    _email = user->getEmail();
    _mobilePhone = user->getMobilePhone();
    _phone = user->getPhone();
    _noSiret = user->getNoSiret();
}


QString User::getFirstname() const
{
    return _firstname;
}

void User::setFirstname(const QString &firstname)
{
    _firstname = firstname;
}

QString User::getLastname() const
{
    return _lastname;
}

void User::setLastname(const QString &lastname)
{
    _lastname = lastname;
}

QString User::getCompany() const
{
    return _company;
}

void User::setCompany(const QString &company)
{
    _company = company;
}

QString User::getTitle() const
{
    return _title;
}

void User::setTitle(const QString &title)
{
    _title = title;
}

QString User::getAddress() const
{
    return _address;
}

void User::setAddress(const QString &address)
{
    _address = address;
}
QString User::getPostalCode() const
{
    return _postalCode;
}

void User::setPostalCode(const QString &postalCode)
{
    _postalCode = postalCode;
}
QString User::getCity() const
{
    return _city;
}

void User::setCity(const QString &city)
{
    _city = city;
}

QString User::getEmail() const
{
    return _email;
}

void User::setEmail(const QString &email)
{
    _email = email;
}
QString User::getMobilePhone() const
{
    return _mobilePhone;
}

void User::setMobilePhone(const QString &mobilePhone)
{
    _mobilePhone = mobilePhone;
}
QString User::getPhone() const
{
    return _phone;
}

void User::setPhone(const QString &phone)
{
    _phone = phone;
}
int User::getNoSiret() const
{
    return _noSiret;
}

void User::setNoSiret(int noSiret)
{
    _noSiret = noSiret;
}
