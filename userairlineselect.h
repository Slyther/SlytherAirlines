#ifndef USERAIRLINESELECT_H
#define USERAIRLINESELECT_H

#include <QMainWindow>
#include <QPushButton>
#include <QLayout>
#include <QtXml>
#include "tdalista.h"
#include "ticketpurchasewindow.h"

class MainMenu;
namespace Ui {
class UserAirlineSelect;
}

class UserAirlineSelect : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserAirlineSelect(QWidget *parent = 0);
    ~UserAirlineSelect();
    MainMenu * parentMenu;
    TDALISTA< TDALISTA<QString>* >* airlines;
    TDALISTA<QPushButton*>* buttons;
    QString dbXMLPath;
    void openXML(QString path);
    void closeEvent(QCloseEvent *ev);
    void show();

private:
    Ui::UserAirlineSelect *ui;
private slots:
    void buttonClicked();
};

#endif // USERAIRLINESELECT_H
