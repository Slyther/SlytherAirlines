#ifndef MAP_H
#define MAP_H
#include <QLabel>
#include <QMouseEvent>
#include "airport.h"
#include "tdalistagrafo.h"

class MainWindow;
class Map : public QLabel
{
public:
    Map(QWidget* parent);
    void mousePressEvent(QMouseEvent *ev);
    void resizeEvent(QResizeEvent *ev);
    TDALISTAGRAFO<Airport*>* airports;
    void paintEvent(QPaintEvent *ev);
    MainWindow * mainwindow;
};

#endif // MAP_H
