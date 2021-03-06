#include "customerstablemodel.h"

namespace Gui {
namespace Widgets {
namespace WdgModels {


CustomersTableModel::CustomersTableModel(
        QObject *parent) : QAbstractTableModel(parent)
{

}

CustomersTableModel::~CustomersTableModel()
{

}

int CustomersTableModel::rowCount(
        const QModelIndex &) const
{
    return _customers.count();
}

int CustomersTableModel::columnCount(
        const QModelIndex &) const
{
    return 7;
}

QVariant CustomersTableModel::data(
        const QModelIndex &index, int role) const
{
    if ((role != Qt::DisplayRole
         && role != Qt::EditRole) || index.row() == -1)
    {
        return QVariant();
    }

    const Customer &customer = _customers[index.row()];
    switch (index.column()) {
    case 0: return customer.getId();
    case 1: return customer.getCompany();
    case 2: return customer.getLastname();
    case 3: return customer.getFirstname();
    case 4: return customer.getPhone();
    case 5: return customer.getEmail();
    case 6: return QString::number(customer.getTurnover(), 'f', 2) + " €";
    default: return QVariant();
    };
}

QVariant CustomersTableModel::headerData(int section,
                                         Qt::Orientation orientation,
                                         int role) const
{
    if (orientation != Qt::Horizontal) {
        return QVariant();
    }

    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    switch (section) {
    case 0: return "ID";
    case 1: return "Société";
    case 2: return "Nom";
    case 3: return "Prénom";
    case 4: return "Téléphone";
    case 5: return "E-mail";
    case 6: return "Chiffre d'affaire";
    default: return QVariant();
    }
}

bool CustomersTableModel::setData(
        const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole) {
        switch(index.column()) {
        case 0:
            _customers[index.row()].setId(value.toInt());
            break;
        case 1:
            _customers[index.row()].setCompany(value.toString());
            break;
        case 2:
            _customers[index.row()].setLastname(value.toString());
            break;
        case 3:
            _customers[index.row()].setFirstname(value.toString());
            break;
        case 4:
            _customers[index.row()].setPhone(value.toString());
            break;
        case 5:
            _customers[index.row()].setEmail(value.toString());
            break;
        case 6:
            break;
        default:
            Log::instance(WARNING) << "Error, in default case of "
                                      "CustomersTableModel::setData";
        }
    }

    return true;
}

void CustomersTableModel::append(
        const Customer &customer)
{
    beginInsertRows(QModelIndex(), _customers.count(), _customers.count());
    _customers.append(customer);
    endInsertRows();
}

void CustomersTableModel::remove(const int i)
{

}

Qt::ItemFlags CustomersTableModel::flags(
        const QModelIndex &index) const
{
    return Qt::ItemIsSelectable |  Qt::ItemIsEditable | Qt::ItemIsEnabled ;
}

int CustomersTableModel::count()
{
    return _customers.count();
}

QList<Customer> CustomersTableModel::getCustomers() const
{
    return _customers;
}

}
}
}
