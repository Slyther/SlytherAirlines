#ifndef AIRPORT_H
#define AIRPORT_H

#include <QLabel>
#include <string>

using namespace std;

class Airport : public QLabel
{
public:
    Airport(QString name, QString code, QPoint pos, QWidget *parent);
    QString name, code;
    QPoint pos, absolutepos;
};

#endif // AIRPORT_H
