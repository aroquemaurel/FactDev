#-------------------------------------------------
#
# Project created by QtCreator 2014-12-18T13:44:51
#
#-------------------------------------------------

QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FactDev
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        log.cpp\
        # Database files
        database/database.cpp \
        # Exceptions
        exceptions/dbexception.cpp \
        parameters.cpp \
        database/customerdatabase.cpp \
        dialogs/dialogaddcustomer.cpp \
        models/customer.cpp

HEADERS  += mainwindow.h \
        log.h\
        # Database files
        database/database.h \
        #Exceptions
        exceptions/dbexception.h \
        parameters.h \
        database/customerdatabase.h \
        models/customer.h \
        dialogs/dialogaddcustomer.h

FORMS    += mainwindow.ui \
        dialogaddcustomer.ui

RESOURCES += \
        Ressources.qrc

OTHER_FILES += \
        sql/createtable.sql \
        sql/removetable.sql
