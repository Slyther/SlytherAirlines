#include "airlinemanager.h"
#include "ui_airlinemanager.h"

AirlineManager::AirlineManager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AirlineManager)
{
    ui->setupUi(this);
    //ui->tableWidget->setColumnWidth(0, this->size().width()-121);

}

AirlineManager::~AirlineManager()
{
    delete ui;
}

void AirlineManager::resizeEvent(QResizeEvent *ev)
{
    ui->tableWidget->setColumnWidth(0, this->size().width()-121);
}
