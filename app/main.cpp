#include "mainwindow.h"
#include "dialogs/userdatadialog.h"
#include <QApplication>
#include "database/database.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    return a.exec();
}
