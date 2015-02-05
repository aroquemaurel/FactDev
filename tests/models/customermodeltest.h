#ifndef CUSTOMERMODELTEST_H
#define CUSTOMERMODELTEST_H
#include "QTestRunner/testrunner.h"
#include "models/customer.h"

using namespace Models;
class CustomerModelTest : public QObject
{
    Q_OBJECT
public:
    CustomerModelTest();
private slots:
    void equals1();
    void equals2();
    void notEquals();

    void commitUpdate();
    void commitInsert();
    void hydrat();
    void remove();
private:
    Customer c1;
    Customer c2;
};
DECLARE_TEST(CustomerModelTest)

#endif // CUSTOMERMODELTEST_H
