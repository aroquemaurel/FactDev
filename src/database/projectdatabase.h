#ifndef PROJECTDATABASE_H
#define PROJECTDATABASE_H
#include "database/database.h"

#include "exceptions/dbexception.h"

#include "models/project.h"

#include "utils/string.h"
#include "utils/log.h"
#include "gui/widgets/widgetsmodels/projectstablemodel.h"

using namespace Utils;
using namespace Exceptions;
using namespace Gui::Widgets;

namespace Databases {

/**
 * @author Florent Berbie
 * @brief The ProjectDatabase class Project table database
 * @see Database
 * @see Project
 */
class ProjectDatabase : public Database
{

public:
    /**
     * @brief ProjectDatabase::getInstance Return an instance of ProjectDatabase
     * @return Instance of ProjectDatabase
     */
    static ProjectDatabase*  instance();

    /**
     * @brief ProjectDatabase::getProject Get informations about the project
     * identified by 'pId'
     * @param pId project
     * @return the project
     */
    Models::Project* getProject(const int pId);

    /**
     * @brief ProjectDatabase::getProject
     * @param q
     * @return
     */
    Models::Project* getProject(QSqlQuery& q);

    /**
     * @brief ProjectDatabase:addProject Add the project 'pProject' to the
     * database
     * @return project id
     */
    int addProject(const Models::Project&);

    /**
     * @brief ProjectDatabase:updateProject Update informations about the
     * project
     */
    void updateProject(const Models::Project&);

    /**
     * @brief removeProject Remove the project with the id 'pId'
     * @param pId project id
     */
    void removeProject(const int pId);

    /**
     * @brief ProjectDatabase:getNbProjects Return the number of projects
     * existing
     * @return number of projects
     */
    int getNbProjects();

    /**
     * @brief Get the number of projects
     * @param customerId If customerId isn't specified if it's not valid,
     * get all projects else get the specified customer projects
     * @return Number of projects in the database for all or for a customer
     */
    int getNbProjects(const int customerId);

    /**
     * @brief getProjectsOfCustomer Return all projects of a customer
     * @param c The customer
     * @return All projects of c with id in key
     */
    QMap<int, Models::Project> getProjectsOfCustomer(
            QSharedPointer<Models::Customer> c, const bool projectLocked=true);

    /**
     * @brief getProjects Return all projects of a customer
     * @param customerId The customer id
     * @return List with all projects of customer
     */
    QList<Models::Project> getProjects(const int customerId);

    /**
      * @brief getProjectsTable Return all projects of a customer in QStandardItemModel
      * @param filter Select only projects who are specified by <i>filter</i>
      * @return QStandardItemModel an item model for QTableView
      */
    WdgModels::ProjectsTableModel* getProjectsTable(const int pId);

    /**
     * @brief getProject Obtain a project without new query
     * @param q The query to use
     * @return The project linked to q
     */
    QSharedPointer<Project> updateProject(QSqlQuery &q);

    /**
     * @brief Project::getAllProjects Return the list of projects
     * @return Projects list
     */
    QList<Project*> getAllProjects();

    /**
     * @brief ProjectDatabase::getCostProjects compute the cost of
     * the project list given in parameter
     * @param projects the list of projects
     * @return the cost of the list given
     */
    double getCostProjects(QList<Project*> projects);

private:
    static ProjectDatabase* _instance;//!< Singleton instance of ProjectDatabase

    /**
     * @brief ProjectDatabase: is a singleton
     */
    ProjectDatabase();

};
}
#endif // PROJECTDATABASE_H
