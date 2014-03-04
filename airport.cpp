#include "airport.h"
#include "tdalista.cpp"

Airport::Airport(string name, string code, QPoint pos, int ID, QWidget* parent) : QLabel()
{
    this->name = name;
    this->code = code;
    this->pos = pos;
    this->ID = ID;
    this->setParent(parent);
    this->relations = new TDALISTA<Relation*>();
    this->setPixmap(QPixmap(QString::fromUtf8(":/map_pin.png")));
    this->setFixedSize(15, 24);
    this->setScaledContents(true);
    this->move(pos - QPoint(this->size().width()/2, this->size().height()));
    this->raise();
}
