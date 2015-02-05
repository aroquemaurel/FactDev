#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "log.h"

namespace Gui {
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    updateTableCustomers();
    updateTree();
    ui->tblCustomers->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->trCustomers->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(
        ui->tblCustomers,
        SIGNAL(customContextMenuRequested(const QPoint &)),
        this,
        SLOT(openContextualMenuTable(const QPoint &)));
    connect(
        ui->trCustomers,
        SIGNAL(customContextMenuRequested(const QPoint &)),
        this,
        SLOT(openContextualMenuTree(const QPoint &)));

    updateUser();
    demo();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::demo() {
    ui->actionNewBill->setVisible(false);
}

int MainWindow::getCurrentTableId(QTableView *tbl) {
    QModelIndex idCell = tbl->model()->index(tbl->currentIndex().row(), 0);
        return tbl->model()->itemData(idCell).value(0).toInt();
}

int MainWindow::getCurrentCustomerId() {
   return getCurrentTableId(ui->tblCustomers);
}

int MainWindow::getCurrentProjectId() {
    return getCurrentTableId(ui->tblProjects);
}


QString MainWindow::getCurrentCustomerName()
{
    QModelIndex index =
            ui->tblCustomers->model()->index(ui->tblCustomers->currentIndex().row(),1);
    return index.model()->itemData(index).value(0).toString();
}

QString MainWindow::getCurrentProjectName()
{
    QModelIndex index = ui->tblProjects->currentIndex();
    return index.data().toString();
}

void MainWindow::addCustomer()
{
    DialogAddCustomer win;
    if(win.exec()) {
        updateTableCustomers();
        updateTree();
    }
}

void MainWindow::editCustomer() {
    if (ui->tblCustomers->selectionModel()->hasSelection()) {
        DialogAddCustomer winAddCustomer(getCurrentCustomerId());
        if(winAddCustomer.exec()) {
            updateTableCustomers();
            updateTree();
        }
    }
}

void MainWindow::removeCustomer() {
    removeItem(ui->tblCustomers, ItemType(ItemType::CUSTOMER, "client"));
    ui->trCustomers->setCurrentIndex(ui->trCustomers->indexAt(QPoint()));
    changeTree();
    updateBtn();
}

void MainWindow::updateUser()
{
    ui->wdgUserData->printUserData();
}

void MainWindow::removeItem(QTableView *tbl, ItemType itemType)
{
    if (tbl->selectionModel()->hasSelection()) {

        if (QMessageBox::warning(
                    this,
                    "Suppression d'"+ QString((itemType.getType() == ItemType::BILLING ? "une " : "un ")) + itemType.getName(),
                    "Voulez vous supprimer " +
                    (itemType.getType() == ItemType::BILLING ?
                            "la " +itemType.getName()+" séléctionnée" :
                            "le "+itemType.getName()+" sélectionné") + " ?",
                    "Supprimer",
                    "Annuler") == 0)
        {
            QModelIndex ls = tbl->selectionModel()->selectedRows().first();
            int pid = tbl->model()->data(ls,Qt::DisplayRole).toInt();
            itemType.getModel(pid)->remove();
            switch(itemType.getType()) {
            case ItemType::CUSTOMER:
                updateTableCustomers();
                break;
            case ItemType::PROJECT:
                updateTableProjects();
                break;
            case ItemType::BILLING:
                break;
            }

            updateTree();
        }
    }
}

void MainWindow::updateTableBillings(const int idProject)
{
    ui->tblQuotes->setModel(
                Database::BillingDatabase::instance()->getBillingsTable(idProject));
    ui->lblQuotes->setText("<b>Devis du projet: "+getCurrentProjectName()+"</b>");
    ui->tblQuotes->hideColumn(0);
    ui->tblQuotes->hideColumn(3);
    ui->tblQuotes->setColumnWidth(1, 200);
    ui->tblQuotes->setColumnWidth(2, 100);
    ui->tblQuotes->setColumnWidth(4, 150);
}

void MainWindow::addQuote()
{
    if (ui->tblCustomers->selectionModel()->hasSelection()) {
        AddQuoteDialog winAddQuote(getCurrentCustomerId());
        winAddQuote.exec();
        updateTableBillings(getCurrentProjectId());

    } else {
        Popup *p = new Popup();
        p->toImplement("\nVeuillez sélectionner un client", this);
    }
}

void MainWindow::editUser()
{
    UserDataDialog userdialog;
    userdialog.exec();
    updateUser();
}

void MainWindow::search() {
    emit search(ui->leSearch->text());
}

void MainWindow::search(QString text)
{
    Search s;
    s.setGroupFilter(ui->gpbxSearchFilter->isChecked());
    s.setSearchInCompanies(ui->chkSearchCompany->isChecked());
    s.setSearchInReferentLastname(ui->chkReferentName->isChecked());
    s.setText(text);
    updateTableCustomers(s.getFilter());
    updateTree(s.getFilter());

    QString styleSearchBackground =
            "background: url(:/icons/searchMini);"
            "background-position: right;"
            "background-repeat: no-repeat;     "
            "border-radius: 0px;"
            "height: 23px;"
            "border: 1px solid #bbb;";
    QString styleSearchNoBackground =
            "border-radius: 0px;"
            "height: 23px;"
            "border: 1px solid #bbb;";

    if(ui->leSearch->text() != "") {
        ui->leSearch->setStyleSheet(styleSearchNoBackground);
    } else {
        ui->leSearch->setStyleSheet(styleSearchBackground);
    }
    s.setGroupFilter(ui->gpbxSearchFilter->isChecked());
    s.setSearchInCompanies(ui->chkSearchCompany->isChecked());
    s.setSearchInReferentLastname(ui->chkReferentName->isChecked());
    s.setText(text);
    updateTableCustomers(s.getFilter());
    updateTree(s.getFilter());
    updateBtn();
}

void MainWindow::openContextualMenuTable(const QPoint point) {
    QMenu* menu = new CustomerContextualMenu(this);

    emit changeCustomerTable();
    QPoint buffPoint = point;
    buffPoint.setX(point.x()+35);
    buffPoint.setY(point.y()+35);
    menu->exec(ui->tblCustomers->mapToGlobal(buffPoint));
}

void MainWindow::openContextualMenuTree(const QPoint point)
{
    QMenu* menu = new CustomerContextualMenu(this);

    emit changeTree();
    QPoint buffPoint = point;
    buffPoint.setX(point.x()+35);
    buffPoint.setY(point.y()+35);
    menu->exec(ui->trCustomers->mapToGlobal(buffPoint));

}

void MainWindow::updateTableCustomers(QString filter) {
    ui->tblCustomers->setModel(
                Database::CustomerDatabase::instance()->getCustomersTable(filter));
    ui->tblCustomers->hideColumn(0);
    ui->tblCustomers->setColumnWidth(0, 100);
    ui->tblCustomers->setColumnWidth(1, 200);
    ui->tblCustomers->setColumnWidth(2, 100);
    ui->tblCustomers->setColumnWidth(3, 150);
    ui->tblCustomers->setColumnWidth(4, 150);
    ui->tblCustomers->setColumnWidth(5, 250);
}

void MainWindow::updateTableProjects(const int pId)
{
    static int lastId = pId;
    if(pId != 0) {
        lastId = pId;
    }
    ui->tblProjects->setModel(Database::ProjectDatabase::instance()->getProjectsTable(lastId));
    ui->tblProjects->hideColumn(0);
}

void MainWindow::updateTree(QString filter)
{
    ui->trCustomers->setModel(
                Database::CustomerDatabase::instance()->getCustomersTree(filter));
    ui->trCustomers->header()->close();
}

void MainWindow::newProject()
{
    QModelIndex index = ui->tblCustomers->currentIndex();
    AddProjectDialog *w;
    if(ui->stackedWidget->currentIndex() == 1) {
        w = new AddProjectDialog(index.row(), 0, 0);
        w->fillFields();
    } else {
        w = new AddProjectDialog(0, 0, 0);
    }
    w->exec();
    updateTree();
    updateTableProjects(getCurrentCustomerId());
}

void MainWindow::removeProject() {
    removeItem(ui->tblProjects, ItemType(ItemType::PROJECT, "projet"));
}

void MainWindow::editProject() {

    QModelIndex index = ui->tblCustomers->currentIndex();

    if (ui->tblProjects->selectionModel()->hasSelection()) {
        AddProjectDialog w(
                    index.row(),
                    getCurrentProjectId());
        w.exec();
    }
}

void MainWindow::aboutQt()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::aboutFact()
{
    MessageBox::showAboutFact();
}

void MainWindow::aboutFactDev() {
    MessageBox::showAboutFactDev();
}

void MainWindow::aboutIcons() {
    MessageBox::showAboutIcons();
}

bool MainWindow::isTreeRoot() {
    return ui->trCustomers->currentIndex().data() == "Tous les clients";
}

bool MainWindow::isProjectItemTree() {
    int i = 0;
    QModelIndex currentIndex = ui->trCustomers->currentIndex();
    while (currentIndex.parent().isValid()) {
        currentIndex = currentIndex.parent();
        i++;
    }
    return i == 1;
}

bool MainWindow::isCustomerItemTree() {
    return !isTreeRoot() && !ui->trCustomers->currentIndex().parent().isValid();
}

bool MainWindow::isQuoteItemTree() {
    return false;
}

void MainWindow::changeTree()
{
    QModelIndex index = ui->trCustomers->currentIndex();
    int idRow = index.row();

    if (isTreeRoot()) {
        ui->stackedWidget->setCurrentIndex(0);
        ui->tblCustomers->clearSelection();
        ui->wdgCustomerData->hide();
        ui->trCustomers->collapseAll();
    }

    if (isCustomerItemTree()) {
        ui->tblCustomers->selectRow(idRow-1);
        ui->wdgCustomerData->printInformations(getCurrentCustomerId());
        ui->trCustomers->collapseAll();
        ui->trCustomers->expand(index);
        changeProjectsTable();
        ui->stackedWidget->setCurrentIndex(1);
    }

    if (isProjectItemTree()) {
        // Need to verify if the current customer is the father
        // Then update TableProjects
        ui->tblCustomers->selectRow(index.parent().row()-1);
        updateTableProjects(getCurrentCustomerId());
        ui->tblProjects->selectRow(idRow);
        updateTableBillings(getCurrentProjectId());
        ui->stackedWidget->setCurrentIndex(2);
    }

    if (isQuoteItemTree()) { // Quote or billing, to define
        //TODO
    }
}

void MainWindow::changeCustomerTable()
{
    ui->wdgCustomerData->printInformations(getCurrentCustomerId());
    updateBtn();
}

void MainWindow::changeProjectsTable()
{
    updateTableProjects(getCurrentCustomerId());
    ui->lblProjects->setText("<b>Projet(s) de: " + getCurrentCustomerName()+"</b>");
    ui->tblProjects->setColumnWidth(0, 100);
    ui->tblProjects->setColumnWidth(1, 150);
    ui->tblProjects->setColumnWidth(2, 200);
    ui->tblProjects->setColumnWidth(3, 122);
    ui->tblProjects->setColumnWidth(4, 122);
    ui->stackedWidget->setCurrentIndex(1);
    updateBtn();
}

void MainWindow::backToCustomersTable()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->actionNewQuote->setEnabled(false);
    ui->actionNewBill->setEnabled(false);
}

void MainWindow::backToProjectsTable()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::quotesProject()
{
    ui->stackedWidget->setCurrentIndex(2);
    updateTableBillings(getCurrentProjectId());
    updateBtn();
}

void MainWindow::updateBtn()
{
    ui->actionNewQuote->setEnabled(ui->tblProjects->currentIndex().row() != -1);
    ui->btnEdit->setEnabled(ui->tblCustomers->currentIndex().row() != -1);
    ui->btnDelCustomer->setEnabled(ui->tblCustomers->currentIndex().row() != -1);
}
}
