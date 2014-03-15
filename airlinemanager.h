#ifndef AIRLINEMANAGER_H
#define AIRLINEMANAGER_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtXml>
#include "tdalista.h"
#include "mainwindow.h"

class MainMenu;
namespace Ui {
class AirlineManager;
}

class AirlineManager : public QMainWindow
{
    Q_OBJECT

public:
    explicit AirlineManager(QWidget *parent = 0);
    ~AirlineManager();
    void resizeEvent(QResizeEvent *ev);
    void closeEvent(QCloseEvent* ev);
    QString dbXMLPath;
    MainMenu * parentMenu;
    TDALISTA< TDALISTA<QString>* >* airlines;
    void openXML(QString path);
    void saveXML(QString path);
    void updateTable();

private slots:
    void on_addNewAirline_clicked();

    void on_manageAirline_clicked();

    void on_removeAirline_clicked();

private:
    Ui::AirlineManager *ui;
};

#endif // AIRLINEMANAGER_H
