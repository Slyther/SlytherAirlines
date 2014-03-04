#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "map.cpp"
#include <QtXml>
#include <QPaintEngine>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->scrollAreaWidgetContents->layout()->setSpacing(0);
    ui->scrollAreaWidgetContents->layout()->setMargin(0);
    ui->scrollAreaWidgetContents->layout()->setContentsMargins(0, 0, 0, 0);
    ui->centralWidget->layout()->setSpacing(0);
    ui->centralWidget->layout()->setMargin(0);
    ui->centralWidget->layout()->setContentsMargins(0, 0, 0, 0);
    ui->sideframe->layout()->setSpacing(0);
    previousSize = this->size();
    ui->ZoomOut->setEnabled(false);
    map = new Map(ui->scrollAreaWidgetContents);
    map->setObjectName(QStringLiteral("Map"));
    map->setScaledContents(true);
    map->setFixedSize(this->size().width()-203, this->size().height()-40);
    ui->horizontalLayout_2->addWidget(map);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    event; //called to make the "unused variable" warning go away during compilation, it's annoying as hell
    if(map->size().width() >= 5760 || map->size().height() >= 3217){
        map->setFixedSize(5760, 3217);
        return;
    }
    QSize t = this->size() - previousSize;
    map->setFixedSize(map->size() + t);
    previousSize = this->size();
}

void MainWindow::on_ZoomIn_clicked()
{
    if(map->size().width()*1.2 >= 5760 || map->size().height()*1.2 >= 3217){
        map->setFixedSize(5760, 3217);
        ui->ZoomIn->setEnabled(false);
    }else{
        map->setFixedSize(map->size() * 1.2);
    }
    ui->ZoomOut->setEnabled(true);
}

void MainWindow::on_ZoomOut_clicked()
{
    if(map->size().width()/1.2 <= this->size().width()-203 || map->size().height()/1.2 <= this->size().height()-40){
        map->setFixedSize(this->size().width()-203, this->size().height()-40);
        ui->ZoomOut->setEnabled(false);
    }else{
        map->setFixedSize(map->size() / 1.2);
    }
    ui->ZoomIn->setEnabled(true);
}

void MainWindow::on_actionOpen_triggered()
{
}

void MainWindow::on_actionSave_triggered()
{

}

void MainWindow::on_actionSave_As_triggered()
{

}
