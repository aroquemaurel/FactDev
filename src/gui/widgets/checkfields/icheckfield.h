#ifndef ICHECKFIELD_H
#define ICHECKFIELD_H

#include <QString>

namespace Gui {
namespace Widgets {
namespace CheckFields {
/**
 * @brief The ICheckField class Interface to check fields validity
 */
class ICheckField {

public:
    /**
     * @brief ICheckField::check Check if the field (line edit) is valid
     * Return TRUE if the field is valid, else FALSE
     * @return boolean Validity of the text
     */
    virtual bool check(QString text) = 0;

};
}
}
}
#endif // ICHECKFIELD_H
