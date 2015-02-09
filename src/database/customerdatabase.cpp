#include "database/customerdatabase.h"

namespace Databases {
CustomerDatabase::CustomerDatabase() throw(DbException*)  : Database() {
    _instances << this;
}

// SINGLETON
CustomerDatabase* CustomerDatabase::_instance = 0;

CustomerDatabase*CustomerDatabase::instance()throw(DbException*)
{
    if (!_instance) {
        _instance = new CustomerDatabase();
    }

    return _instance;
}


QStandardItemModel* CustomerDatabase::getCustomersTable(QString filter)
throw(DbException*)
{
    QStandardItemModel* retour = new QStandardItemModel();

    retour->setColumnCount(5);
    retour->setHorizontalHeaderLabels(
                QStringList()
                << ("Id")
                << ("Société")
                << ("Nom")
                << ("Prénom")
                << ("Téléphone")
                << ("EMail")
                );
    QSqlQuery q;


    q.prepare("SELECT idCustomer ,firstnameReferent, lastnameReferent, company,"
              " phone, email "
              "FROM Customer "
              "WHERE 1 "+filter+" "
              "ORDER BY UPPER(company), UPPER(lastnameReferent)");

    if(!q.exec()) {
        throw new DbException(
                    "Impossible d'obtenir la liste des Customers",
                    "CustomerDatabase::getCustomersTable",
                    lastError(q),
                    1.1);
    }

    while(q.next()) {
        QList<QStandardItem*> ligne;

        ligne << new QStandardItem(value(q, "idCustomer").toString());
        ligne << new QStandardItem(
                     Utils::String::firstLetterToUpper(value(q,"company").toString()));
        ligne << new QStandardItem(
                     value(q, "lastnameReferent").toString().toUpper());
        ligne << new QStandardItem(Utils::String::firstLetterToUpper(
                                       value(q, "firstNameReferent").toString()));
        ligne << new QStandardItem(value(q, "phone").toString());
        ligne << new QStandardItem(value(q, "email").toString());

        retour->appendRow(ligne);
    }

    return retour;
}

QStandardItemModel* CustomerDatabase::getCustomersTree(QString filter)
throw(DbException*)
{
    QStandardItemModel* retour = new QStandardItemModel();

    QSqlQuery q;

    q.prepare("SELECT * "
              "FROM Customer WHERE 1 "+filter+" "
              "ORDER BY UPPER(company), UPPER(lastnameReferent)");

    if(!q.exec()) {
        throw new DbException(
                    "Impossible d'obtenir la liste des Customers",
                    "CustomerDatabase::getCustomersTree",
                    lastError(q),
                    1.1);
    }

    QStandardItem* item = new QStandardItem("Tous les clients");
    item->setIcon(QIcon(":icons/customer"));
    retour->appendRow(item);

    while(q.next()) {
        QStandardItem* item;

        if(value(q,"company").toString().isEmpty()) {
            item = new QStandardItem(
                        value(q, "lastnameReferent").toString().toUpper()
                        + " "
                        +Utils::String::firstLetterToUpper(value(q,"firstnameReferent").toString()));
        } else {
            item = new
                QStandardItem(Utils::String::firstLetterToUpper(value(q,"company").toString()));
        }

        item->setIcon(QIcon(":icons/customer"));

        // Project for a customer
        QSqlQuery q2;

        q2.prepare("SELECT *"
                   "FROM Project WHERE idCustomer = :idCustom "
                   "ORDER BY UPPER(name), UPPER(description)");
        q2.bindValue(":idCustom",value(q, "idCustomer").toString());

        if(!q2.exec()) {
            throw new DbException(
                        "Impossible d'obtenir la liste des Projects",
                        "CustomerDatabase::getCustomersTree",
                        lastError(q),
                        1.1);
        }

        while(q2.next()) {
            QStandardItem *child = new QStandardItem(value(q2,"name").toString());
            child->setIcon(QIcon(":icons/img/project"));
            item->appendRow(child);
        }

        retour->appendRow(item);
    }

    return retour;
}

QSharedPointer<Models::Customer> CustomerDatabase::getCustomer(const int pId) {
    QSqlQuery q;
    QSharedPointer<Models::Customer> customer;

    q.prepare("SELECT * FROM Customer WHERE idCustomer = :pId");
    q.bindValue(":pId", pId);

    if(!q.exec()) {
        throw new DbException(
                    "Impossible d'ajouter le Customer",
                    "BddCustomer::getCustomer",
                    lastError(q),
                    1.2);
    }

    if(q.first()) {
        customer = QSharedPointer<Models::Customer>(new Models::Customer());
        customer->setId(value(q, "idCustomer").toInt());
        customer->setFirstnameReferent(value(q,"firstnameReferent").toString());
        customer->setLastnameReferent(value(q,"lastnameReferent").toString());
        customer->setCompany(value(q,"company").toString());
        customer->setAddress(value(q,"address").toString());
        customer->setPostalCode(value(q,"postalCode").toString());
        customer->setCity(value(q,"city").toString());
        customer->setCountry(value(q,"country").toString());
        customer->setEmail(value(q,"email").toString());
        customer->setMobilePhone(value(q,"mobilePhone").toString());
        customer->setPhone(value(q,"phone").toString());
        customer->setFax(value(q,"fax").toString());
    }

    return customer;
}


int CustomerDatabase::addCustomer(const Models::Customer& pCustomer) {
    QSqlQuery q;

    q.prepare(
                "INSERT INTO Customer "
                "(firstnameReferent, lastnameReferent, company, address, "
                "postalCode, city, country, email, mobilePhone, phone, fax)"
                " VALUES "
                "(:firstnameReferent, :lastnameReferent, :company, :address, "
                ":postalCode, :city, :country, :email, :mobilePhone, :phone, :fax)"
                );

    q.bindValue(":firstnameReferent", pCustomer.getFirstnameReferent());
    q.bindValue(":lastnameReferent", pCustomer.getLastnameReferent());
    q.bindValue(":company", pCustomer.getCompany());
    q.bindValue(":address", pCustomer.getAddress());
    q.bindValue(":postalCode", pCustomer.getPostalCode());
    q.bindValue(":city", pCustomer.getCity());
    q.bindValue(":country", pCustomer.getCountry());
    q.bindValue(":email", pCustomer.getEmail());
    q.bindValue(":mobilePhone", pCustomer.getMobilePhone());
    q.bindValue(":phone", pCustomer.getPhone());
    q.bindValue(":fax", pCustomer.getFax());

    if(!q.exec()) {
        throw new DbException(
                    "Impossible d'ajouter le Customer",
                    "BddCustomer::addCustomer",
                    lastError(q),
                    1.3);
    }

    return q.lastInsertId().toInt();
}

void CustomerDatabase::updateCustomer(const Models::Customer &pCustomer) {
    QSqlQuery q;
    q.prepare(
                "UPDATE Customer SET "
                "firstnameReferent=:firstname, lastnameReferent=:lastname,"
                "company=:company, address=:address, postalCode=:postalCode, city=:city,"
                "country=:country, email=:email, mobilePhone=:mobilePhone, phone=:phone,"
                "fax=:fax "
                "WHERE idCustomer=:idCustomer");

    q.bindValue(":idCustomer", pCustomer.getId());

    q.bindValue(":firstname", pCustomer.getFirstnameReferent());
    q.bindValue(":lastname", pCustomer.getLastnameReferent());
    q.bindValue(":company", pCustomer.getCompany());
    q.bindValue(":address", pCustomer.getAddress());
    q.bindValue(":phone", pCustomer.getPhone());
    q.bindValue(":postalCode", pCustomer.getPostalCode());
    q.bindValue(":city", pCustomer.getCity());
    q.bindValue(":country", pCustomer.getCountry());
    q.bindValue(":email", (pCustomer.getEmail()));
    q.bindValue(":mobilePhone", pCustomer.getMobilePhone());
    q.bindValue(":phone", pCustomer.getPhone());
    q.bindValue(":fax", pCustomer.getFax());

    if(!q.exec()) {
        throw new DbException(
                    "Impossible d'éditer les informations du Customer",
                    "BddCustomer::updateCustomer",
                    lastError(q),
                    1.4);
    }

}

void CustomerDatabase::removeCustomer(const int pId)
{
    QSqlQuery q;
    q.prepare(
                "DELETE FROM Customer "
                "WHERE idCustomer=:pId"
                );

    q.bindValue(":pId", pId);

    if(!q.exec()) {
        throw new DbException(
                    "Impossible d'éditer les informations du Customer",
                    "BddCustomer::removeCustomer",
                    lastError(q),
                    1.5);
    }

}

int CustomerDatabase::getNbCustomers() {
    QSqlQuery q;

    q.prepare("SELECT count(idCustomer) AS nb_p FROM Customer");

    if(!q.exec()) {
        throw new DbException(
                    "Impossible d'éditer les informations du Customer",
                    "BddCustomer::getNbCustomers",
                    lastError(q),
                    1.6);
    }
    q.next();

    return value(q, "nb_p").toInt();
}
}
