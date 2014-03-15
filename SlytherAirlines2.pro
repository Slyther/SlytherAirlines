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
    mainmenu.cpp \
    airlinemanager.cpp \
    logindg.cpp \
    relationsmanager.cpp \
    userairlineselect.cpp \
    ticketpurchasewindow.cpp \
    usermap.cpp

HEADERS  += mainwindow.h \
    airport.h \
    map.h \
    mainmenu.h \
    airlinemanager.h \
    logindg.h \
    edge.h \
    node.h \
    tdalista.h \
    tdalistagrafo.h \
    vertex.h \
    relationsmanager.h \
    userairlineselect.h \
    ticketpurchasewindow.h \
    usermap.h

FORMS    += mainwindow.ui \
    mainmenu.ui \
    airlinemanager.ui \
    admincp.ui \
    logindg.ui \
    relationsmanager.ui \
    userairlineselect.ui \
    ticketpurchasewindow.ui

RESOURCES += \
    res.qrc
