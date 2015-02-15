#include "billingmodeltest.h"
#include "gui/dialogs/userdatadialog.h"

BillingModelTest::BillingModelTest()
{
}

void BillingModelTest::setup() {
    b1 = new Billing();
    b1->setId(7);
    b1->setTitle("Maitre boucher");
    b1->setDescription("Découpe de viande");
    b1->setNumber(1);
    b1->setDate(QDate(2012,12,21));
    b1->setIsBilling(false);

    b2 = new Billing();
    b2->setId(7);
    b2->setTitle("Maitre boucher");
    b2->setDescription("Découpe de viande");
    b2->setNumber(1);
    b2->setDate(QDate(2012,12,21));
    b2->setIsBilling(false);
}

void BillingModelTest::equals1()
{
    setup();
    QVERIFY(*b1 == *b2);
}

void BillingModelTest::equals2()
{
    setup();
    b1->setDescription("Découpe de cheval");
    QVERIFY(!(*b1 == *b2));
}

void BillingModelTest::notEquals()
{
    setup();
    b1->setDescription("Découpe de cheval");
    QVERIFY(*b1 != *b2);
}

void BillingModelTest::commitUpdate()
{
    // TODO implementation
    /*
    int id = BillingDatabase::instance()->addBilling(b1);
    b1->setId(id);
    b1->setDescription("Découpe de poulet");
    b1->commit();
    Billing *b2 = BillingDatabase::instance()->getBilling(id);
    QVERIFY(b1 == *b2);*/
}

void BillingModelTest::commitInsert()
{
    setup();
    b1->setId(0);
    b1->commit();
    Billing *b2 = Databases::BillingDatabase::instance()->getBilling(b1->getId());
    QVERIFY(*b1 == *b2);
}

void BillingModelTest::hydrat()
{
    setup();
    Billing b2 = Billing(1);
    b1->setId(1);
    b1->setTitle("Coucou");
    b1->setDescription("Mon super devis de la mort qui rox du poulet");
    b1->setNumber(1);
    b1->setIsBilling(false);
    b1->setDate(QDate(2015,02,13));

//    QVERIFY(*b1 == b2);
}

void BillingModelTest::hydratWithContributories() {
    setup();
    QMap<Project *, QList<Contributory> > contributories = Billing(24).getContributories();
    QCOMPARE(contributories.count(), 2);

    // we only check id… Remaining are already tested (getProject, getContributory)
    for(auto i = contributories.begin(); i != contributories.end() ; ++i) {
        switch(i.key()->getId()) {
        case 21:
            QCOMPARE(i.value().count(), 3);
            QCOMPARE(i.value().at(0).getId(), 59);
            QCOMPARE(i.value().at(1).getId(), 60);
            QCOMPARE(i.value().at(2).getId(), 61);
            break;
        case 44:
            QCOMPARE(i.value().count(), 1);
            QCOMPARE(i.value().at(0).getId(), 62);
            break;
        default:
            QFAIL("Default case");
        }
    }
}
