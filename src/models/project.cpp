#include "project.h"
#include "database/projectdatabase.h"
Project::Project()
{
}

Project::Project(QString name)
{
    _name = name;
}

Project::Project(int id)
{
    _id = id;
}

void Project::commit() {
    if(_id == 0) {
        _id = ProjectDatabase::instance()->addProject(*this);
    } else if(_toRemoved) {
        remove();
    } else {
        ProjectDatabase::instance()->updateProject(*this);
    }
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
double Project::getDailyRate() const
{
    return _dailyRate;
}

void Project::setDailyRate(double dailyRate)
{
    _dailyRate = dailyRate;
}
Customer* Project::getCustomer() const
{
    return _customer;
}

void Project::setCustomer(Customer* customer)
{
    _customer = customer;
}




