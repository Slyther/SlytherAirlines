#include "mainwindow.h"
#include "mainmenu.cpp"
#include <QApplication>
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainMenu w;
    MainWindow w;
    w.show();
    return a.exec();
}
