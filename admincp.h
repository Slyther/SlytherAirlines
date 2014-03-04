#ifndef ADMINCP_H
#define ADMINCP_H

#include <QMainWindow>

namespace Ui {
class AdminCP;
}

class AdminCP : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminCP(QWidget *parent = 0);
    ~AdminCP();

private:
    Ui::AdminCP *ui;
};

#endif // ADMINCP_H
