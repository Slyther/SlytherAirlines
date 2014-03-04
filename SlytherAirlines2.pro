#-------------------------------------------------
#
# Project created by QtCreator 2014-02-25T02:54:32
#
#-------------------------------------------------

QT       += core gui
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SlytherAirlines2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    airport.cpp \
    map.cpp \
    relation.cpp \
    noded.cpp \
    tdalista.cpp \
    mainmenu.cpp \
    airlinemanager.cpp \
    admincp.cpp \
    logindg.cpp

HEADERS  += mainwindow.h \
    airport.h \
    map.h \
    relation.h \
    noded.h \
    tdalista.h \
    mainmenu.h \
    airlinemanager.h \
    admincp.h \
    logindg.h

FORMS    += mainwindow.ui \
    mainmenu.ui \
    airlinemanager.ui \
    admincp.ui \
    logindg.ui

RESOURCES += \
    res.qrc
