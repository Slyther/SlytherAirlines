#include "map.h"
#include <QDebug>
#include <QPainter>
#include "mainwindow.h"

Map::Map(QWidget *parent) : QLabel()
{
    this->setParent(parent);
    this->setPixmap(QPixmap(QString::fromUtf8(":/minimap.png")));
    airports = new TDALISTAGRAFO<Airport*>();
}

void Map::mousePressEvent(QMouseEvent *ev)
{
    if(mainwindow->isEditting())
        return;
    if(airports->size() != 0){
        if(airports->end()->name != "Default" && airports->end()->code != "Default")
            airports->add(new Airport("Default", "Default", ev->pos(), this->parentWidget()));
    }else{
        airports->add(new Airport("Default", "Default", ev->pos(), this->parentWidget()));
    }
    airports->end()->pos = ev->pos();
    airports->end()->absolutepos = QPoint(airports->end()->pos.x() * double(5760)/double(this->size().width()), airports->end()->pos.y() * double(3217)/double(this->size().height()));
    airports->end()->show();
    update();
    mainwindow->insertNewAirport();
}

void Map::resizeEvent(QResizeEvent *ev)
{
    ev;
    update();
}

void Map::paintEvent(QPaintEvent *ev)
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
    }
    QPainter painter(this);
    for(int i = 0; i < airports->size(); i++){
        for(int j = 0; j < airports->size(); j++){
            if(airports->isAdjacent(i, j)){
                 painter.drawLine(airports->get(i)->pos, airports->get(j)->pos);
            }
        }
    }
}
