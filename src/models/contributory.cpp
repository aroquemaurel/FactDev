#include "contributory.h"

#include "database/contributorydatabase.h"
using namespace Databases;

namespace Models {
Contributory::Contributory()
{
    _description = "";
    _quantity = 0.;
    _id = 0;
    _toRemoved = false;
    _project = new Project();
    _hourlyRate = 0.0;
}

Contributory::Contributory(int id)
{
    _hourlyRate = 0.0;
    hydrat(id);
    _id = id;
}

Contributory::~Contributory()
{
    // TODO… seg fault :-/
//    delete _project;
}

void Contributory::commit()
{
    if(_id == 0) {
        _id = ContributoryDatabase::instance()->addContributory(*this);
    } else if(_toRemoved) {
        remove();
    } else {
        ContributoryDatabase::instance()->updateContributory(*this);
    }
}

void Contributory::hydrat(int id)
{
    Contributory* c = ContributoryDatabase::instance()->getContributory(id);
    _description = c->getDescription();
    _quantity = c->getQuantity();
    _unit = c->getUnit();
    _project = c->getProject();
    delete c;
}


void Contributory::remove()
{
    ContributoryDatabase::instance()->removeContributory(_id);
}

double Contributory::getPrice(const bool paied)
{
    double ret = 0.0;
    if(_hourlyRate == 0.0) {
        _hourlyRate = _project->getDailyRate()/User(1).getNbHoursPerDays();
    }
    if(_unit.getype() == HOUR) {
        ret = _quantity * _hourlyRate;
    } else {
        ret = _quantity * _hourlyRate * User(1).getNbHoursPerDays();
    }

    return ret;
}

double Contributory::getSumQuantity()
{
    double ret;
    if(_unit.getype() == DAY) {
        ret = _quantity;
    } else {
        ret = _quantity / User(1).getNbHoursPerDays();
    }
    return ret;
}

QVariantHash Contributory::getDataMap()
{
    QVariantHash data;

    data["project"] = _project->getName();
    data["nbHours"] = _quantity;
    data["contributoryDescription"] = _description;
    data["contributoryLongDescription"] = _longDescription;
    return data;
}

Project* Contributory::getProject() const
{
    return _project;
}

void Contributory::setProject(Project* id)
{
    _project = id;
}
double Contributory::getQuantity() const
{
    return _quantity;
}

void Contributory::setQuantity(double value)
{
    _quantity = value;
}
QString Contributory::getDescription() const
{
    return _description;
}

void Contributory::setDescription(const QString &description)
{
    _description = description;
}

bool Contributory::operator ==(const Contributory &c)
{
    return (getDescription() == c.getDescription() &&
            getQuantity() == c.getQuantity() && getUnit() == c.getUnit());
}

bool Contributory::operator !=(const Contributory &c)
{
    return !(*this == c);
}
QString Contributory::getLongDescription() const
{
    return _longDescription;
}

void Contributory::setLongDescription(const QString &longDescription)
{
    _longDescription = longDescription;
}
Unit Contributory::getUnit() const
{
    return _unit;
}

void Contributory::setUnit(const Unit &value)
{
    _unit = value;
}
double Contributory::getHourlyRate() const
{
    return _hourlyRate;
}

void Contributory::setHourlyRate(double value)
{
    _hourlyRate = value;
}



}

