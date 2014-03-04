#ifndef MAP_H
#define MAP_H
#include <QLabel>
#include <QMouseEvent>
#include "airport.h"
#include "relation.h"
#include "tdalista.h"

class Map : public QLabel
{
public:
    Map(QWidget* parent);
    void mousePressEvent(QMouseEvent *ev);
    void resizeEvent(QResizeEvent *ev);
    TDALISTA<Airport*>* airports;
    void paintEvent(QPaintEvent *ev);
};

#endif // MAP_H
