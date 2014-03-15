#include "usermap.h"
#include <QDebug>
#include <QPainter>
#include "ticketpurchasewindow.h"
#include "ui_ticketpurchasewindow.h"

UserMap::UserMap(QWidget *parent) : QLabel()
{
    this->setParent(parent);
    this->setPixmap(QPixmap(QString::fromUtf8(":/minimap.png")));
    airports = new TDALISTAGRAFO<Airport*>();
    currentPath = new TDALISTA<Airport*>();
}

void UserMap::resizeEvent(QResizeEvent *ev)
{
    ev;
    update();
}

void UserMap::paintEvent(QPaintEvent *ev)
{
    QLabel::paintEvent(ev);
    for(int i = 0; i < airports->size(); i++){
        if(airports->get(i) == mainwindow->currentAirport)
            airports->get(i)->setPixmap(QPixmap(QString::fromUtf8(":/map_pin2.png")));
        else
            airports->get(i)->setPixmap(QPixmap(QString::fromUtf8(":/map_pin.png")));
        airports->get(i)->pos.setX(double(airports->get(i)->absolutepos.x()) * double(double(this->size().width())/double(5760)));
        airports->get(i)->pos.setY(double(airports->get(i)->absolutepos.y()) * double(double(this->size().height())/double(3217)));
        airports->get(i)->move(airports->get(i)->pos - QPoint(airports->get(i)->size().width()/2, airports->get(i)->size().height()));
        if(airports->get(i) == mainwindow->currentAirport)
            airports->get(i)->show();
        else
            airports->get(i)->setVisible(false);
    }
    QPainter painter(this);
    for(int i = 0; i < currentPath->size(); i++){
        currentPath->get(i)->show();
        if(i > 0){
            painter.drawLine(currentPath->get(i-1)->pos, currentPath->get(i)->pos);
        }
        if(i == currentPath->size()-1 && i != 0){
            currentPath->get(i)->setPixmap(QPixmap(QString::fromUtf8(":/map_pin3.png")));
        }
    }
}
