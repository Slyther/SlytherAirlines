#ifndef USERMAP_H
#define USERMAP_H
#include <QLabel>
#include <QMouseEvent>
#include "airport.h"
#include "tdalistagrafo.h"
#include "tdalista.h"

class TicketPurchaseWindow;
class UserMap : public QLabel
{
public:
    UserMap(QWidget* parent);
    void resizeEvent(QResizeEvent *ev);
    TDALISTAGRAFO<Airport*>* airports;
    TDALISTA<Airport*>* currentPath;
    void paintEvent(QPaintEvent *ev);
    TicketPurchaseWindow * mainwindow;
};

#endif // USERMAP_H
