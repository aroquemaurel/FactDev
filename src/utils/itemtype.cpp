#include "itemtype.h"

namespace Utils {
ItemType::ItemType(int type, QString name)
{
    _type = type;
    _name = name;
}
QString ItemType::getName() const
{
    return _name;
}

void ItemType::setName(const QString &name)
{
    _name = name;
}

Models::IModel* ItemType::getModel(int id) {
    Models::IModel* ret(0);

    switch(_type) {
    case ItemType::BILLING:
    case ItemType::QUOTE:
        ret = new Models::Billing(id);
        break;
    case ItemType::CUSTOMER:
        ret = new Models::Customer(id);
        break;
    case ItemType::PROJECT:
        ret = new Models::Project(id);
        break;
    default:
        Log::instance(WARNING) << "MainWindow::removeItem bad item type";
    }

    return ret;
}
int ItemType::getType() const
{
    return _type;
}

void ItemType::setType(int type)
{
    _type = type;
}
}

