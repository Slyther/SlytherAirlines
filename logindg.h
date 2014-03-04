#ifndef LOGINDG_H
#define LOGINDG_H

#include <QMainWindow>
#include "admincp.h"
class MainMenu;
namespace Ui {
class LoginDg;
}

class LoginDg : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginDg(QWidget *parent = 0);
    ~LoginDg();
    MainMenu *parentMenu;
    AdminCP *admincp;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::LoginDg *ui;
};

#endif // LOGINDG_H
