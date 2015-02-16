#ifndef BILLINGDATABASETEST_H
#define BILLINGDATABASETEST_H
#include <QtTest/QtTest>
#include "QTestRunner/testrunner.h"

#include "models/billing.h"

#include "database/billingdatabase.h"

using namespace Models;
class BillingDatabaseTest : public QObject
{
    Q_OBJECT
public:
     BillingDatabaseTest();

private slots:
     void insert();
     void remove();
     void update();
     void selectBillingNotFound();
     void selectBillingFound();
     void addBillingProject();
     void removeBillingProject();
private:
     Billing* b1;
     int _lastInsert;


     void setup();
};

DECLARE_TEST(BillingDatabaseTest)

#endif // BILLINGDATABASETEST_H
