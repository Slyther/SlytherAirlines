#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "map.h"
#include "airport.h"
#include "relationsmanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void resizeEvent(QResizeEvent* event);
    void insertNewAirport();
    void openXML(QString path);
    void saveXML(QString path);
    bool isEditting();
    bool changed, loaded;
    void closeEvent(QCloseEvent *event);
    Airport * currentAirport;
    QSize previousSize;
    Map* map;
    QString XMLPath;
    ~MainWindow();

private slots:
    void on_ZoomOut_clicked();
    void on_ZoomIn_clicked();
    void on_newAirportOk_clicked();
    void on_AddOk_clicked();
    void on_AirportsBox_currentIndexChanged(int index);
    void on_SaveChangesOk_clicked();
    void on_EditRelationsOk_clicked();
    void on_RemovePortOk_clicked();

    void on_actionBack_to_Airlines_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
