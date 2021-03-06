#ifndef DATABASESETTINGSWIDGET_H
#define DATABASESETTINGSWIDGET_H

#include <QWidget>

namespace Ui {
    class DatabaseSettingsWidget;
}

namespace Gui {
namespace Widgets {

/**
 * @author
 * @brief The DatabaseSettingsWidget class Windows of database settings
 */
class DatabaseSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief DatabaseSettingsWidget::DatabaseSettingsWidget Construct a
     * DatabaseSettingsWidget
     * @param parent Parent widget of this windows
     */
    explicit DatabaseSettingsWidget(QWidget *parent = 0);
    ~DatabaseSettingsWidget();

    /**
     * @brief DatabaseSettingsWidget::fillFields Complete fields with a default
     * value for field Database name, Username, IP address and port
     */
    void fillFields();

    /**
     * @brief DatabaseSettingsWidget::getDatabaseName Return the database name
     * @return Database name
     */
    QString getDatabaseName();

    /**
     * @brief DatabaseSettingsWidget::getLogin Return the login of the user
     * @return Login of the user
     */
    QString getLogin();

    /**
     * @brief DatabaseSettingsWidget::getPassword Return the password of the
     * user
     * @return User password
     */
    QString getPassword();

    /**
     * @brief DatabaseSettingsWidget::getDomainNameOrIP Return the domain name
     * or IP address on the machine where is the database
     * @return Domain name or IP address
     */
    QString getDomainNameOrIP();

    /**
     * @brief DatabaseSettingsWidget::getPort Return the port of the database
     * @return Database port
     */
    QString getPort();

public slots:

    /**
     * @brief DatabaseSettingsWidget::isValid Return TRUE if all fields are
     * correctly inputed else FALSE
     * @return boolean
     */
    bool isValid();

    /**
     * @brief DatabaseSettingsWidget::checkRepeatLogin Check if the second login
     *  field is the same than the first
     */
    void checkRepeatPassword(QString text);

    /**
     * @brief DatabaseSettingsWidget::userInterfaceChanged User interface has
     * changed
     */
    void userInterfaceChanged();

signals:
    /**
     * @brief DatabaseSettingsWidget::textfieldChanged Signal which indicates if
     *  a fieldtext has changed
     */
    void textfieldChanged();

private:
    Ui::DatabaseSettingsWidget *ui; //!< User interface
};

}
}
#endif // DATABASESETTINGSWIDGET_H
