#include "searchtest.h"
#include "models/customer.h"
#include "database/customerdatabase.h"
searchTest::searchTest()
{

}

void searchTest::searchAll()
{
    _search.setGroupFilter(false);
    _search.setText("facilisis");

    QVERIFY(_search.getFilter() == "AND (0 OR company LIKE '%facilisis%' OR lastnameReferent LIKE '%facilisis%' OR p.name LIKE '%facilisis%'  AND bp.idProject = p.idProject  OR bp.idContributory = ( SELECT idContributory FROM Contributory WHERE 0 OR description LIKE '%facilisis%' ) AND 1 OR bp.idBilling = ( SELECT idBilling FROM Billing WHERE 0 OR title LIKE '%facilisis%'  OR 0 ))");
    QStandardItemModel* model = Databases::CustomerDatabase::instance()->getCustomersTable(_search.getFilter());
    QVERIFY(model->data(model->index(0, 2)).toString().toUpper() == "MIDDLETON");
}

void searchTest::searchCompanyName()
{
    _search.setGroupFilter(true);
    _search.setSearchInCompanies(true);
    _search.setSearchInReferentLastname(false);
    _search.setText("facilisis");
    QVERIFY(_search.getFilter() == "AND (0 OR company LIKE '%facilisis%' )");
    QStandardItemModel* model = Databases::CustomerDatabase::instance()->getCustomersTable(_search.getFilter());
    QVERIFY(model->data(model->index(0, 2)).toString().toUpper() == "MIDDLETON");
}
void searchTest::searchCompanyNameWithSimpleQuote()
{
    _search.setGroupFilter(true);
    _search.setSearchInCompanies(true);
    _search.setSearchInReferentLastname(false);
    _search.setText("facil'isis'");
    QVERIFY(_search.getFilter() == "AND (0 OR company LIKE '%facil''isis''%' )");

    QStandardItemModel* model = Databases::CustomerDatabase::instance()->getCustomersTable(_search.getFilter());
    QVERIFY(model->data(model->index(0, 2)) == QVariant::Invalid);
}

void searchTest::searchReferentLastname()
{
    _search.setGroupFilter(true);
    _search.setSearchInCompanies(false);
    _search.setSearchInReferentLastname(true);
    _search.setText("middleton");
    QVERIFY(_search.getFilter() == "AND (0 OR lastnameReferent LIKE '%middleton%')");
    QStandardItemModel* model = Databases::CustomerDatabase::instance()->getCustomersTable(_search.getFilter());
    QVERIFY(model->data(model->index(0, 2)).toString().toUpper() == "MIDDLETON");

}

void searchTest::searchWithoutFilters()
{
    _search.setGroupFilter(true);
    _search.setSearchInCompanies(false);
    _search.setSearchInReferentLastname(false);
    _search.setText("larson");

    QVERIFY(_search.getFilter() == "AND (0 )");
    QStandardItemModel* model = Databases::CustomerDatabase::instance()->getCustomersTable(_search.getFilter());
    QVERIFY(model->data(model->index(0, 2)) == QVariant::Invalid);

}


