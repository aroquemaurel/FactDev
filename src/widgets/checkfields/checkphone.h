#ifndef CHECKPHONE_H
#define CHECKPHONE_H
#include "checkuntilfield.h"

/**
 * @brief The CheckPhone class Line Edit of Phone number with a check icon
 */
class CheckPhone : public CheckUntilField
{
public:
    /**
     * @brief CheckPhone::CheckPhone Construct a CheckPhone
     * @param w QWidget linked to <b>CheckPhone</b>
     */
    CheckPhone(QWidget* w = 0, QPushButton* btn=0);

};

#endif // CHECKPHONE_H
