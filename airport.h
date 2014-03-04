#ifndef AIRPORT_H
#define AIRPORT_H

#include <QLabel>
#include <string>
#include "relation.h"
#include "tdalista.h"

using namespace std;

class Airport : public QLabel
{
public:
    Airport(string name, string code, QPoint pos, int ID, QWidget *parent);
    string name, code;
    QPoint pos, absolutepos, minimumpos;
    TDALISTA<Relation*>* relations;
    int ID;
};

#endif // AIRPORT_H
