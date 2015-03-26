#include "contributory.h"

#include "database/contributorydatabase.h"
using namespace Databases;

namespace Models {
Contributory::Contributory()
{
    _description = "";
    quantity = 0.;
    _id = 0;
    _toRemoved = false;
    _project = new Project();
}

Contributory::Contributory(int id)
{
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
    quantity = c->getQuantity();
    _unit = c->getUnit();
    _project = c->getProject();
    delete c;
}


void Contributory::remove()
{
    ContributoryDatabase::instance()->removeContributory(_id);
}

QVariantHash Contributory::getDataMap()
{
    QVariantHash data;

    data["project"] = _project->getName();
    data["nbHours"] = quantity;
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
    return quantity;
}

void Contributory::setQuantity(double value)
{
    quantity = value;
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


}

