#include "admincp.h"
#include "ui_admincp.h"

AdminCP::AdminCP(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminCP)
{
    ui->setupUi(this);
}

AdminCP::~AdminCP()
{
    delete ui;
}
