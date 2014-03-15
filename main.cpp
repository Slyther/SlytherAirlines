#include "mainmenu.h"
#include "userairlineselect.h"
#include <QApplication>
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainMenu w;
    w.show();
    return a.exec();
}
