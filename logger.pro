#-------------------------------------------------
#
# Project created by QtCreator 2012-09-11T15:17:45
#
#-------------------------------------------------

QT       += core gui sql

TARGET = logger
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    map.cpp \
    about.cpp \
    help.cpp \
    dbconnection.cpp \
    reglament.cpp \
    newdatabaseconfirmation.cpp \
    dialog.cpp \
    regions.cpp

HEADERS  += mainwindow.h \
    map.h \
    about.h \
    help.h \
    dbconnection.h \
    reglament.h \
    newdatabaseconfirmation.h \
    dialog.h \
    regions.h

FORMS    += mainwindow.ui \
    map.ui \
    about.ui \
    help.ui \
    reglament.ui \
    newdatabaseconfirmation.ui \
    dialog.ui \
    regions.ui

RESOURCES += \
    AppResources.qrc

RC_FILE = myapp.rc

TRANSLATIONS = log73_ru.ts
