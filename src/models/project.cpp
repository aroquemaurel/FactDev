#include "project.h"

Project::Project()
{
}

void Project::commit()
{
    // TODO implement me !
}

void Project::hydrat(int id)
{
    // TODO implement me !
}

void Project::remove()
{
    // TODO implement me !
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
double Project::geDailyRate() const
{
    return _dailyRate;
}

void Project::setDailyRate(double dailyRate)
{
    _dailyRate = dailyRate;
}
Customer Project::getCustomer() const
{
    return _customer;
}

void Project::setCustomer(Customer customer)
{
    _customer = customer;
}



