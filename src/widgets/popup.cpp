#include "popup.h"

void Popup::toImplement(QString str, QWidget* w)
{
    QMessageBox::critical
            (w,
             "Non implémenté",
             "La fonction demandée n'est pas encore implémenté.<br/>"+
             str,
             "OK");
    Log::instance(WARNING) << "TODO Implement me" << str;

}