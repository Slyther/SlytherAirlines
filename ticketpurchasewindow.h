#ifndef TICKETPURCHASEWINDOW_H
#define TICKETPURCHASEWINDOW_H

#include <QMainWindow>
#include "usermap.h"
#include "airport.h"

namespace Ui {
class TicketPurchaseWindow;
}

class UserAirlineSelect;
class TicketPurchaseWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TicketPurchaseWindow(QWidget *parent = 0);
    void resizeEvent(QResizeEvent* event);
    void openXML(QString path);
    void show();
    void closeEvent(QCloseEvent *event);
    TDALISTA<QLabel*> *labels;
    UserAirlineSelect *parentManager;
    Airport * currentAirport;
    QSize previousSize;
    UserMap* map;
    QString XMLPath;
    ~TicketPurchaseWindow();
    Ui::TicketPurchaseWindow *ui;

private slots:
    void on_ZoomOut_clicked();
    void on_ZoomIn_clicked();

    void on_actionBack_to_Airlines_triggered();

    void on_AirportsBox_currentIndexChanged(int index);

    void on_AirportsBox_2_currentIndexChanged(int index);

private:

};

#endif // TICKETPURCHASEWINDOW_H
