#include "airport.h"

Airport::Airport(QString name, QString code, QPoint pos, QWidget* parent) : QLabel()
{
    this->name = name;
    this->code = code;
    this->pos = pos;
    this->setParent(parent);
    this->setPixmap(QPixmap(QString::fromUtf8(":/map_pin.png")));
    this->setFixedSize(15, 24);
    this->setScaledContents(true);
    this->move(pos - QPoint(this->size().width()/2, this->size().height()));
    this->raise();
}
