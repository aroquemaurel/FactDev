#ifndef BILLING_H
#define BILLING_H
#include <QString>
#include <QDate>
#include <QMap>
#include <QList>
#include <QIcon>

#include "models/imodel.h"
#include "models/project.h"
#include "models/contributory.h"
#include "models/user.h"
#include "models/contributorieslist.h"
#include "models/calculable.h"

#include "database/contributorydatabase.h"

#include "generator/texgenerator.h"
#include "generator/pdfgenerator.h"

#include "utils/double.h"
namespace Models {
/**
 * @author Antoine de Roquemaurel
 * @author Florent Berbie
 * @brief The Billing class : Billing or Quote of a Customer
 */
class Billing : public IModel, public Calculable
{
public:
    /**
     * @brief Billing::Billing. Construct a Billing.
     */
    Billing();
    /**
     * @brief Billing::Billing. Construct a Billing or quote.
     * @param int id
     */
    Billing(int id);
    /**
     * @brief destruct a billing object
     */
    ~Billing();

    /**
     * @brief Billing::commit. Insert a modification
     * in Billing table on the database.
     */
    void commit();

    /**
     * @brief Billing::hydrat. Update of the Billing which is specified
     * by <i>getId</i>
     * @param getId
     */
    void hydrat(int getId);

    /**
     * @brief Billing::remove. Remove a Billing.
     */
    void remove();

    /**
     * @brief Billing::getDataMap Get all data of model with a HashMap key/value
     * @return Model's data
     */
    QVariantHash getDataMap();

    /**
     * @brief getPrice Return the price of a calculable object
     * @return The price
     */
    double getPrice(bool paied=false);

    /**
     * @brief ContributoriesList::getSumQuantity Return the sum of quantity
     * (number of days) of the Contributories
     * @return sum of quantity in days
     */
    double getSumQuantity();

    /**
     * @brief Billing::generateTex Generate a .tex file for the billing
     */
    void generateTex();

    /**
     * @brief Billing::generatePdf Generate a .pdf file for the billing
     */
    void generatePdf();

    /**
     * @brief Billing::getPath Return the path of billing filename (without
     * extension)
     * @return billing path
     */
    QString getPath();

    /**
     * @brief Billing::getFolder Return the directory of billing
     * @return Billing directory
     */
    QString getFolder();

    /**
     * @brief Billing::getFilename Return the filename of billing (without
     * extension)
     * @return Filename of Bulling
     */
    QString getFilename();
    /**
     * @brief Billing::getContributories. Return a map of <b>Contributory</b>
     * for each <b>Project</b> of the <b>Billing</b>
     * @return QMap<Project, QList<Contributory>>
     */
    ContributoriesList &getContributories();

    /**
     * @brief Billing::addContributories Add a new contributory for project p
     * @param p The Project who contain Contributory
     * @param c The new Contributory
     */
    void addContributory(Contributory &c);

    /**
     * @brief Billing::getTitle. return title of <b>Billing</b>
     * @return title of Billing
     */
    QString getTitle() const;

    /**
     * @brief Billing::setTitle. Modify the title of <b>Billing</b>
     * @param getTitle Modify the title with <i>getTitle</i>
     */
    void setTitle(const QString &getTitle);

    /**
     * @brief Billing::getDescription. return description of <b>Billing</b>
     * @return description of Billing
     */
    QString getDescription() const;

    /**
     * @brief Billing::setDescription. Modify the description of <b>Billing</b>
     * @param getDescription Modify the description with <i>getDescription</i>
     */
    void setDescription(const QString &getDescription);

    /**
     * @brief Billing::getNumber. Return number of the <b>Billing</b>.
     * @return _number of Billing
     */
    int getNumber() const;

    /**
     * @brief Billing::setNumber. Modify <i>_number</i> of Billing.
     * @param getNumber the new number of the Billing
     */
    void setNumber(int getNumber);

    /**
     * @brief Billing::isBilling. Return if it's a billing or a quote.
     * @return if it's billing or a quote
     */
    bool isBilling() const;

    /**
     * @brief Billing::setIsBilling. Modify <i>isBilling</i>
     * of <b>Billing</b>.
     * @param isBilling
     */
    void setIsBilling(bool isBilling);

    /**
     * @brief Billing::getDate. return date of the <b>Billing</b>
     * @return date of Billing
     */
    QDate getDate() const;

    /**
     * @brief Billing::setDate. Modify <i>date</i> of the <b>Billing</b>
     * @param getDate the new date of the Billing
     */
    void setDate(const QDate &getDate);
    /**
     * @brief Billing::isPaid Return TRUE if thee current billing is paid else
     * return FALSE
     * @return Boolean
     */
    bool isPaid() const;

    /**
     * @brief Billing::setIsPaid Define the current billing according the
     * argument <i>isPaid</i>
     * @param isPaid Boolean
     */
    void setIsPaid(bool isPaid);

    /**
     * @brief Billing::operator == define the operator "==" to compare two
     * billings and to see if they are the same
     * @param b the <b>Billing</b> to compare with the current <b>Billing</b>
     * @return true if they are the same billings else false
     */
    bool operator ==(const Billing &b);
    /**
     * @brief Billing::operator != defines the operator "!=" to compare two
     * <b>Billing</b> and to see if they are different
     * @param b the <b>Billing</b> to compare with the current <b>Billing</b>
     * @return true if the <b>Billing</b> are different else false
     */
    bool operator !=(const Billing &b);
    void setContributories(const ContributoriesList &contributories);

    /**
     * @brief Billing::operator < defines the operator "< to compare two
     * <b>Billing</b> and to see if the fisrt is anterior to the second
     * @param b the <b>Billing</b> to compare with the current <b>Billing</b>
     * @return true if the <b>Billing</b> are different else false
     */
    bool operator <(const Billing &b) const;


    /**
     * @brief Billing::getItem Return the bill/quote item
     * @return QStandardItem an item for QTree (level/depth 3)
     */
    QStandardItem* getItem();

private:
    ContributoriesList _contributories; //!< List of contributories
    QString _title;                     //!< Title of billing
    QString _description;               //!< Description of a billing
    int _number;                        //!< Number of billing
    bool _isBilling;                    //!< Is a billing… Or if a quote
    QDate _date;                        //!< Date for billing
    bool _isPaid;                       //!< Billing is Paid
};

}
#endif // BILLING_H
