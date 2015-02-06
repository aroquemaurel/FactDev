#ifndef DIALOGADDCUSTOMER_H
#define DIALOGADDCUSTOMER_H

#include <QDialog>
#include "models/customer.h"

using namespace Models;

namespace Ui {
class DialogAddCustomer;
}

namespace Gui {
namespace Dialogs {

/**
 * @author Cédric Rohaut
 * @brief The DialogAddCustomer class Window to add or modify a Customer
 */
class DialogAddCustomer : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief DialogAddCustomer Construct a window to add/modify a Customer
     * @param id Customer id
     * @param parent QWidget parent
     */
    explicit DialogAddCustomer(int id = 0, QWidget *parent = 0);
    ~DialogAddCustomer();

    /**
     * @brief fillFields If the Customer exits, fill line edits with the data of
     * the current Customer
     */
    void fillFields();

    /**
     * @brief accept Valid data inputed by user and add these data in Database
     */
    void accept();

    /**
     * @brief reject Cancel the operation and close the windows
     */
    void reject();
public slots:
    /**
     * @brief setFieldsComponents
     */
    void checkFields();

private:
    QSharedPointer<Models::Customer> _custom;
    Ui::DialogAddCustomer *ui;
};
}
}
#endif // DIALOGADDCUSTOMER_H