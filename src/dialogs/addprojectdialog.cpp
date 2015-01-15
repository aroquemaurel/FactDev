#include "dialogs/addprojectdialog.h"
#include "ui_addprojectdialog.h"
#include "database/customerdatabase.h"

AddProjectDialog::AddProjectDialog(int id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddProjectDialog)
{

    _project = Project(id);
    ui->setupUi(this);
    //ui->cbCustomer->setModel(customerData.instance()->getCustomersTable());
    ui->cbCustomer->setModel(CustomerDatabase::instance()->getCustomersTable());


}

AddProjectDialog::~AddProjectDialog()
{
    delete ui;
}

void AddProjectDialog::accept()
{

    _project.setName(ui->leNameProject->text());
    _project.setDescription(ui->leDescription->toPlainText());
    _project.setDailyRate(ui->widget->getDailyRate());
    _project.setCustomer(
        ui->cbCustomer->itemData(ui->cbCustomer->currentIndex()).toInt());

    _project.commit();
    QDialog::accept();
}

void AddProjectDialog::reject()
{
    QDialog::reject();
}

void AddProjectDialog::fillCustomerComboBox()
{
    //CustomerDatabase customerData;


}
