#ifndef UTILS_H
#define UTILS_H

#include <QString>

namespace Utils {
/**
 * @brief The Utils class
 * @author Antoine de Roquemaurel
 */
class String
{
public:
    /**
     * @brief firstLetterToUpper Put the first letter of a string in capslock
     * @param s The string to display
     * @return The new string with caps
     */
    static QString firstLetterToUpper(QString s);
};
}
#endif // UTILS_H