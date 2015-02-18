#include "contributorieswidget.h"
#include "models/contributory.h"
#include "gui/widgets/delegates/projectcombodelegate.h"
#include "gui/widgets/delegates/doublespinboxdelegate.h"
#include "gui/widgets/delegates/unitcombodelegate.h"
#include "models/contributorieslist.h"
#include "ui_contributorieswidget.h"

namespace Gui {
namespace Widgets {

ContributoriesWidget::ContributoriesWidget(QSharedPointer<Customer> c, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContributoriesWidget)
{
    ui->setupUi(this);
    _modelProjects = new WdgModels::ProjectContributoriesTableModel();
    _customer = c;
    Delegates::ProjectComboDelegate* d = new Delegates::ProjectComboDelegate(c);
    d->setLocked(true);
    ui->tblProjects->setItemDelegateForColumn(0, d);
    ui->tblProjects->setItemDelegateForColumn(1, new Delegates::DoubleSpinBoxDelegate());
    ui->tblProjects->setItemDelegateForColumn(2, new Delegates::DoubleSpinBoxDelegate());
    ui->tblProjects->setModel(_modelProjects);
    ui->btnAddPrestation->hide();
    ui->btnRmovePrestation->hide();
    connect(ui->tblProjects->itemDelegateForColumn(0), SIGNAL(closeEditor(QWidget*)), SLOT(editing()));
    emit contributoryChanged();
    emit updateBtn();
}

ContributoriesWidget::~ContributoriesWidget()
{
    delete ui;
}

ContributoriesList* ContributoriesWidget::getContributories() const
{
    int i = 0;
    ContributoriesList* contribList = new ContributoriesList();
    for(QPair<Models::Project*, Models::Rate> pair : _modelProjects->getProjects()) {
        contribList->addProject(pair.first, pair.second);

        for(Contributory& c : _modelsContributories[i++]->getContributories()) {
            c.setProject(pair.first);
            contribList->addContributory(c);
        }
    }
    return contribList;
}

void ContributoriesWidget::add()
{
    _modelsContributories[ui->stack->currentIndex()]->append(Contributory());
    emit contributoryChanged();
}

void ContributoriesWidget::add(Contributory& c)
{
    _modelsContributories[ui->stack->currentIndex()]->append(c);
    emit contributoryChanged();
}

void ContributoriesWidget::add(QList<Contributory>& contributories)
{
    for(Contributory& c : contributories) {
        add(c);
    }
}

void ContributoriesWidget::remove(void)
{
//    if (ui->tblContributories->selectionModel()->hasSelection()) {
//        _modelContributories->remove(ui->tblContributories->currentIndex().row());
//    }
    emit contributoryChanged();
}

void ContributoriesWidget::addProject(void)
{
    qDebug() << "Yeah ! I add a new project :)";
    _modelProjects->append();
    QTableView* view = new QTableView();
    _modelsContributories << new WdgModels::ContributoriesTableModel();
    view->setModel(_modelsContributories.last());
    view->setEditTriggers(QAbstractItemView::DoubleClicked);
    view->setItemDelegateForColumn(1, new Delegates::DoubleSpinBoxDelegate());
    view->setItemDelegateForColumn(2, new Delegates::UnitComboDelegate());
    view->setColumnWidth(0, 450);
    view->setColumnWidth(1, 100);
    view->setColumnWidth(2, 100);

    ui->stack->insertWidget(ui->stack->count(), view);
    emit updateBtn();
//    table->horizontalHeader()->setResizeMode( 0, QHeaderView::Stretch );
//    table->horizontalHeader()->setResizeMode( 1, QHeaderView::ResizeToContents );
}

void ContributoriesWidget::removeProject(void)
{
    qDebug() << "I want to remove this project :-(";
    _modelProjects->remove(ui->tblProjects->currentIndex().row());
    ui->stack->removeWidget(ui->stack->currentWidget());
    emit updateBtn();
}

void ContributoriesWidget::changeProject()
{
    ui->stack->setCurrentIndex(ui->tblProjects->currentIndex().row());
    emit updateBtn();
}

void ContributoriesWidget::editing()
{
    ((Delegates::ProjectComboDelegate*)ui->tblProjects->itemDelegateForColumn(0))->removeInCombo(_modelProjects->getSelectedProjects());
    emit updateBtn();
}

void ContributoriesWidget::updateBtn()
{
    ui->btnAddProject->setEnabled(_modelProjects->getSelectedProjects().count() <
                                  ((Delegates::ProjectComboDelegate*)ui->tblProjects->itemDelegateForColumn(0))->getProjects().count() &&
                                  _modelProjects->allProjectsChose());
    ui->btnRemoveProject->setEnabled(ui->tblProjects->currentIndex().row() != -1);

    if(_modelProjects->getSelectedProjects().count() > 0) {
        ui->btnAddPrestation->show();
        ui->btnRmovePrestation->show();
    } else {
        ui->btnAddPrestation->hide();
        ui->btnRmovePrestation->hide();
    }
}

int ContributoriesWidget::count() {
    //return _modelContributories->count();
}

}
}
