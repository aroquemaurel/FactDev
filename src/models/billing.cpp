#include "billing.h"
#include "database/billingdatabase.h"

Billing::Billing()
{
}

Billing::Billing(int id)
{
    hydrat(id);
}

void Billing::commit()
{
    if(_id == 0) {
        _id = BillingDatabase::instance()->addBilling(*this);
    } else if(_toRemoved){
        remove();
    } else {
        BillingDatabase::instance()->updateBilling(*this);
    }
}

void Billing::hydrat(int id)
{
    _id = id;
    Billing *quote = BillingDatabase::instance()->getBilling(id);
    _title = quote->getTitle();
    _description = quote->getDescription();
    _number = quote->getNumber();
    _date = quote ->getDate();
    _contributories = quote->getContributories();

}

void Billing::remove()
{
    BillingDatabase::instance()->removeBilling(_id);
}

QMap<Project*, QList<Contributory*>*> Billing::getContributories() const
{
    return _contributories;
}

void Billing::setContributories(QMap<Project*, QList<Contributory*>*> contributories)
{
    _contributories = contributories;
}

void Billing::addContributories(Project* p, Contributory* c)
{
    _contributories.value(p)->push_back(c);
}

QString Billing::getTitle() const
{
    return _title;
}

void Billing::setTitle(const QString &title)
{
    _title = title;
}

QString Billing::getDescription() const
{
    return _description;
}

void Billing::setDescription(const QString &description)
{
    _description = description;
}

int Billing::getNumber() const
{
    return _number;
}

void Billing::setNumber(int number)
{
    _number = number;
}
bool Billing::isBilling() const
{
    return _isBilling;
}

void Billing::setIsBilling(bool isBilling)
{
    _isBilling = isBilling;
}

QDate Billing::getDate() const
{
    return _date;
}

void Billing::setDate(const QDate &date)
{
    _date = date;
}





