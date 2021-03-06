#ifndef STARTEDWINDOWSDIALOG_H
#define STARTEDWINDOWSDIALOG_H

#include <QDialog>
#include "models/user.h"
#include "database/accessdatabase.h"
#include "gui/utils/windowsettings.h"
namespace Ui {
class StartedWindowsDialog;
}

using namespace Models;

namespace Gui {
namespace Dialogs {

/**
 * @author Florent Berbie
 * @brief The StartedWindowsDialog class Contruct a Windows for the first begin
 * @see DatabaseSettingsWidget
 */
class StartedWindowsDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief StartedWindowsDialog::StartedWindowsDialog Contruct a
     * StartedWindowsDialog
     * @param parent QWidget parent
     */
    explicit StartedWindowsDialog(QWidget *parent = 0);
    ~StartedWindowsDialog();

    /**
     * @brief StartedWindowsDialog::fillFields Fill line edits with the data of
     *  the user
     */
    void fillFields();

    /**
     * @brief StartedWindowsDialog::getImage Return a scaled image from the
     * icon specified by it <i>path</i>. The image returned has a resolution of
     * <i>width</i>*<i>height</i> (default 256*256)
     * @param path Icon path
     * @param width Icon width
     * @param height Icon height
     * @return Scaled image
     */
    QPixmap getImage(QString path, int width = 256, int height = 256);

    /**
     * @brief StartedWindowsDialog::isDatabaseTypeValid Return TRUE if settings
     * of database type is valid else return FALSE
     * @return boolean on the database type validity
     */
    bool isDatabaseTypeValid();

    /**
     * @brief StartedWindowsDialog::isDatabaseCentralized Return TRUE if the
     * current type of database is centralized else FALSE
     * @return boolean
     */
    bool isDatabaseCentralized();

public slots:
    /**
     * @brief StartedWindowsDialog::checkFields Check all fields of dialog
     * components
     */
    void checkFields();

    /**
     * @brief StartedWindowsDialog::backToPage2 Return to the second page
     */
    void backToPage2();

    /**
     * @brief StartedWindowsDialog::nextToPage2 Go to the second page
     */
    void nextToPage2();

    /**
     * @brief StartedWindowsDialog::nextToPage3 Go to the third page
     */
    void nextToPage3();

    /**
     * @brief StartedWindowsDialog::databaseTypeChanged Listener on the
     * Database type combobox
     * @param index Current index selected
     */
    void databaseTypeChanged(const int index);

    /**
     * @brief StartedWindowsDialog::databaseTypeChanged Listener on the
     * Database type combobox
     */
    void databaseTypeChanged(void);

    /**
     * @brief StartedWindowsDialog::updateNextButton Check if the next button is
     *  enabled
     */
    void updateNextButton();

    /**
     * @brief StartedWindowsDialog::accept Valid data inputed by user and add
     * these data in Database
     */
    void accept();


private:
    Ui::StartedWindowsDialog *ui;   //!< User Interface
    User* _user;                    //!< User of the software
};

}
}
#endif // STARTEDWINDOWSDIALOG_H
