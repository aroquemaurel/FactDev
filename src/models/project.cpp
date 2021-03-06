#include "project.h"

#include "database/projectdatabase.h"
#include "database/billingdatabase.h"
#include "models/billing.h"

using namespace Databases;

namespace Models {

Project::Project()
{
    _id = 0;
    _toRemoved = false;
    _cost = 0.0;

}

Project::Project(QString name)
{
    _id = 0;
    _toRemoved = false;
    _name = name;
    _cost = 0.0;
}

Project::Project(int id)
{
    _id = id;
    _toRemoved = false;
    hydrat(id);
}

Project::~Project()
{
    _customer.reset();
}

void Project::commit() {
    if(_id == 0) {
        _beginDate = QDate::currentDate();
        _id = ProjectDatabase::instance()->addProject(*this);
    } else if(_toRemoved) {
        remove();
    } else {
        ProjectDatabase::instance()->updateProject(*this);
    }
}

void Project::hydrat(int id)
{
    Project* p = ProjectDatabase::instance()->getProject(id);
    _id = id;
    _name = p->getName();
    _description = p->getDescription();
    _beginDate = p->getBeginDate();
    _endDate = p->getEndDate();
    _dailyRate = p->getDailyRate();
    _customer = p->getCustomer();
}

void Project::remove()
{
    ProjectDatabase::instance()->removeProject(_id);
}

QVariantHash Project::getDataMap()
{
    return QVariantHash();
}

void Project::lock()
{
    _endDate = QDate::currentDate();
}

void Project::unlock() {
    _endDate = QDate();
}

bool Project::isLocked() const {
    return !_endDate.isNull() && _endDate <= QDate::currentDate();
}

QString Project::getName() const
{
    return _name;
}

void Project::setName(const QString &name)
{
    _name = name;
}
QString Project::getDescription() const
{
    return _description;
}

void Project::setDescription(const QString &description)
{
    _description = description;
}

QDate Project::getBeginDate() const
{
    return _beginDate;
}

void Project::setBeginDate(QDate beginDate)
{
    _beginDate = beginDate;
}

QDate Project::getEndDate() const
{
    return _endDate;
}

void Project::setEndDate(QDate endDate)
{
    _endDate = endDate;
}

double Project::getCost() const
{
    double ret(0.0);
    QList<Billing> bills =
            Databases::BillingDatabase::instance()->getBillsPaid(_id);
//    QList<Billing> bills = Databases::BillingDatabase::instance()->getBillings(_id);
    for (Billing bill : bills) {
        ContributoriesList cl = Databases::ContributoryDatabase::instance()
                ->getContributoriesByBillingAndProject(bill.getId(), _id);
        Rate rate = Databases::RateDatabase::instance()->getRate(bill.getId(),
                                                                 _id);
        ret += (cl.getSumQuantity()) * rate.getDailyRate();
    }
    return ret;
}

double Project::getDailyRate() const
{
    return _dailyRate;
}

void Project::setDailyRate(double dailyRate)
{
    _dailyRate = dailyRate;
}
QSharedPointer<Customer> Project::getCustomer() const
{
    return _customer;
}

void Project::setCustomer(QSharedPointer<Customer> customer)
{
    _customer = customer;
}

bool Project::operator ==(const Project &p)
{
    return  getName() == p.getName()
            && getDescription() == p.getDescription()
            && getCustomer() == getCustomer();
}

bool Project::operator <(const Project &p) const
{
    return getBeginDate() < p.getBeginDate();
}

bool Project::operator !=(const Project &p)
{
    return !(*this == p);
}

}
