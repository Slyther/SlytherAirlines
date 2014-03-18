#include "relationsmanager.h"
#include "ui_relationsmanager.h"
#include "mainwindow.h"
#include <QMessageBox>

RelationsManager::RelationsManager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RelationsManager)
{
    ui->setupUi(this);
    this->setFixedSize(800, 449);
    ui->AirportsList->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->RelationsList->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->AirportsList->setEditTriggers(QAbstractItemView::EditTriggers(0));
    ui->RelationsList->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->RelationsList->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->AirportsList->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->AirportsList->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->AddOk->setEnabled(false);
    ui->RemoveOk->setEnabled(false);
    changed = false;
}

RelationsManager::~RelationsManager()
{
    delete ui;
}

void RelationsManager::loadLists()
{
    this->setWindowTitle(QString("Relations Manager for %1 Airport").arg(mainwindow->map->airports->get(indexOfCurrent)->name));
    for(int i = 0; i < mainwindow->map->airports->size(); i++){
        if(i == indexOfCurrent)
            continue;
        if(mainwindow->map->airports->isAdjacent(indexOfCurrent, i)){
            ui->RelationsList->insertRow(ui->RelationsList->rowCount());
            ui->RelationsList->setItem(ui->RelationsList->rowCount()-1, 0, new QTableWidgetItem(mainwindow->map->airports->get(i)->name));
            ui->RelationsList->setItem(ui->RelationsList->rowCount()-1, 1, new QTableWidgetItem(mainwindow->map->airports->get(i)->code));
            ui->RelationsList->setItem(ui->RelationsList->rowCount()-1, 2, new QTableWidgetItem(QString::number(mainwindow->map->airports->adjacencyValue(indexOfCurrent, i))));
            continue;
        }
        ui->AirportsList->insertRow(ui->AirportsList->rowCount());
        ui->AirportsList->setItem(ui->AirportsList->rowCount()-1, 0, new QTableWidgetItem(mainwindow->map->airports->get(i)->name));
        ui->AirportsList->setItem(ui->AirportsList->rowCount()-1, 1, new QTableWidgetItem(mainwindow->map->airports->get(i)->code));
    }
    updateSizes();
}

void RelationsManager::updateSizes()
{
    for(int i = 0; i < ui->RelationsList->rowCount(); i++){
        ui->RelationsList->setRowHeight(i, 20);
    }
    for(int i = 0; i < ui->AirportsList->rowCount(); i++){
        ui->AirportsList->setRowHeight(i, 20);
    }
    if(ui->RelationsList->rowCount() > 0){
        ui->RelationsList->setColumnWidth(0, (ui->AirportsList->size().width()/3)-16/3);
        ui->RelationsList->setColumnWidth(1, (ui->AirportsList->size().width()/3)-16/3);
        ui->RelationsList->setColumnWidth(2, (ui->AirportsList->size().width()/3)-16/3);
    }else{
        ui->RelationsList->setColumnWidth(0, ui->AirportsList->size().width()/3);
        ui->RelationsList->setColumnWidth(1, ui->AirportsList->size().width()/3);
        ui->RelationsList->setColumnWidth(2, ui->AirportsList->size().width()/3);
    }
    if(ui->AirportsList->rowCount() > 0){
        ui->AirportsList->setColumnWidth(0, (ui->AirportsList->size().width()/2)-8);
        ui->AirportsList->setColumnWidth(1, (ui->AirportsList->size().width()/2)-8);
    }else{
        ui->AirportsList->setColumnWidth(0, ui->AirportsList->size().width()/2);
        ui->AirportsList->setColumnWidth(1, ui->AirportsList->size().width()/2);
    }
    ui->lineEdit->setText("0");
}

void RelationsManager::on_AddOk_clicked()
{
    if(ui->AirportsList->selectedItems().count() == 0)
        return;
    QRegExp re("\\d*");
    if(!re.exactMatch(ui->lineEdit->text())){
        QMessageBox *msg = new QMessageBox(QMessageBox::Information, "Invalid Information!", "Price needs to be a valid number.", QMessageBox::Ok, this, Qt::Popup);
        msg->setWindowModality(Qt::NonModal);
        msg->setDefaultButton(QMessageBox::Ok);
        msg->exec();
        return;
    }
    for(int i = 0; i < mainwindow->map->airports->size(); i++){
        if(mainwindow->map->airports->get(i)->code == ui->AirportsList->selectedItems().at(1)->text()){
            mainwindow->map->airports->addEdge(indexOfCurrent, i, ui->lineEdit->text().toInt());
            break;
        }
    }
    ui->RelationsList->insertRow(ui->RelationsList->rowCount());
    ui->RelationsList->setItem(ui->RelationsList->rowCount()-1, 0, new QTableWidgetItem(ui->AirportsList->selectedItems().at(0)->text()));
    ui->RelationsList->setItem(ui->RelationsList->rowCount()-1, 1, new QTableWidgetItem(ui->AirportsList->selectedItems().at(1)->text()));
    ui->RelationsList->setItem(ui->RelationsList->rowCount()-1, 2, new QTableWidgetItem(ui->lineEdit->text()));
    ui->AirportsList->removeRow(ui->AirportsList->currentRow());
    ui->AirportsList->selectRow(0);
    updateSizes();
    changed = true;
}

void RelationsManager::on_RemoveOk_clicked()
{
    if(ui->RelationsList->selectedItems().count() == 0)
        return;
    for(int i = 0; i < mainwindow->map->airports->size(); i++){
        if(mainwindow->map->airports->get(i)->code == ui->RelationsList->selectedItems().at(1)->text()){
            mainwindow->map->airports->removeEdge(indexOfCurrent, i);
            break;
        }
    }
    ui->AirportsList->insertRow(ui->AirportsList->rowCount());
    ui->AirportsList->setItem(ui->AirportsList->rowCount()-1, 0, new QTableWidgetItem(ui->RelationsList->selectedItems().at(0)->text()));
    ui->AirportsList->setItem(ui->AirportsList->rowCount()-1, 1, new QTableWidgetItem(ui->RelationsList->selectedItems().at(1)->text()));
    ui->RelationsList->removeRow(ui->RelationsList->currentRow());
    ui->RelationsList->selectRow(0);
    updateSizes();
    changed = true;
}

void RelationsManager::on_AirportsList_clicked(const QModelIndex &index)
{
    index;
    ui->AddOk->setEnabled(true);
    ui->RemoveOk->setEnabled(false);
}

void RelationsManager::on_RelationsList_clicked(const QModelIndex &index)
{
    index;
    ui->AddOk->setEnabled(false);
    ui->RemoveOk->setEnabled(true);
}

void RelationsManager::closeEvent(QCloseEvent *ev)
{
    ev;
    mainwindow->map->update();
    if(changed){
        if(!mainwindow->changed && mainwindow->loaded){
            mainwindow->changed = true;
        }
    }
}
