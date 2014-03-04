#include "map.h"
#include "tdalista.cpp"
#include "noded.cpp"
#include <QDebug>
#include <QPainter>

Map::Map(QWidget *parent) : QLabel()
{
    this->setParent(parent);
    this->setPixmap(QPixmap(QString::fromUtf8(":/minimap.png")));
    airports = new TDALISTA<Airport*>();
}

void Map::mousePressEvent(QMouseEvent *ev)
{
    airports->add(new Airport("Default", "Default", ev->pos(), 0, this->parentWidget()));
    airports->end()->absolutepos = QPoint(airports->end()->pos.x() * double(double(5760)/double(this->size().width())), airports->end()->pos.y() * double(3217)/double(double(this->size().height())));
    airports->end()->show();
}

void Map::resizeEvent(QResizeEvent *ev)
{
    for(int i = 0; i < airports->size(); i++){
        airports->get(i)->pos.setX(double(airports->get(i)->absolutepos.x()) * double(double(this->size().width())/double(5760)));
        airports->get(i)->pos.setY(double(airports->get(i)->absolutepos.y()) * double(double(this->size().height())/double(3217)));
        airports->get(i)->move(airports->get(i)->pos - QPoint(airports->get(i)->size().width()/2, airports->get(i)->size().height()));
    }
}

void Map::paintEvent(QPaintEvent *ev)
{
    QLabel::paintEvent(ev);
}
