#ifndef AIRLINEMANAGER_H
#define AIRLINEMANAGER_H

#include <QMainWindow>

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

private:
    Ui::AirlineManager *ui;
};

#endif // AIRLINEMANAGER_H
