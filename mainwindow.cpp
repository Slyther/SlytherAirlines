#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "map.h"
#include <QtXml>
#include <QPaintEngine>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    changed = false;
    loaded = false;
    XMLPath = "../test.xml";
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
    map->mainwindow = this;
    currentAirport = 0;
    ui->AddOk->setEnabled(false);
    ui->SaveChangesOk->setEnabled(false);
    ui->EditRelationsOk->setEnabled(false);
    ui->RemovePortOk->setEnabled(false);
    ui->AirportsBox->addItem("");
    openXML(XMLPath);
    loaded = true;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    event;
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

void MainWindow::insertNewAirport()
{
    currentAirport = map->airports->end();
    ui->PosXLine->setText(QString::number(currentAirport->absolutepos.x()));
    ui->PosYLine->setText(QString::number(currentAirport->absolutepos.y()));
    ui->AddOk->setEnabled(true);
    ui->newAirportOk->setEnabled(false);
}

void MainWindow::on_newAirportOk_clicked()
{
    if(currentAirport != 0){
        QMessageBox *msg = new QMessageBox(QMessageBox::Information, "An airport is being worked on!", "An airport is currently being worked on. Finish working on it by clicking \"Save Changes\".", QMessageBox::Ok, this, Qt::Popup);
        msg->setWindowModality(Qt::NonModal);
        msg->setDefaultButton(QMessageBox::Ok);
        msg->exec();
        return;
    }
    QString name = ui->NameLine->text();
    QString code = ui->CodeLine->text();
    if(name.isEmpty() || code.isEmpty()){
        QMessageBox *msg = new QMessageBox(QMessageBox::Information, "Information missing!", "In order to add airports you need a name and a code.", QMessageBox::Ok, this, Qt::Popup);
        msg->setWindowModality(Qt::NonModal);
        msg->setDefaultButton(QMessageBox::Ok);
        msg->exec();
        return;
    }
    if(ui->PosXLine->text().isEmpty() || ui->PosYLine->text().isEmpty()){
        QMessageBox *msg = new QMessageBox(QMessageBox::Information, "Information missing!", "In order to add airports you need a its position on the map.", QMessageBox::Ok, this, Qt::Popup);
        msg->setWindowModality(Qt::NonModal);
        msg->setDefaultButton(QMessageBox::Ok);
        msg->exec();
        return;
    }
    QRegExp re("\\d*");
    if(!re.exactMatch(ui->PosXLine->text()) || !re.exactMatch(ui->PosYLine->text())){
        QMessageBox *msg = new QMessageBox(QMessageBox::Information, "Invalid Information!", "Coordinates need to be valid numbers.", QMessageBox::Ok, this, Qt::Popup);
        msg->setWindowModality(Qt::NonModal);
        msg->setDefaultButton(QMessageBox::Ok);
        msg->exec();
        return;
    }
    int labelposx = ui->PosXLine->text().toInt();
    int labelposy = ui->PosYLine->text().toInt();
    if(labelposx < 0 || labelposx > 5760 || labelposy < 0 ||labelposy > 3217){
        QMessageBox *msg = new QMessageBox(QMessageBox::Information, "Incorrect information!", "Invalid coordinates. Please input valid coordinates and try again.", QMessageBox::Ok, this, Qt::Popup);
        msg->setWindowModality(Qt::NonModal);
        msg->setDefaultButton(QMessageBox::Ok);
        msg->exec();
        return;
    }
    for(int i = 0; i < map->airports->size(); i++){
        if(map->airports->get(i)->name == name || map->airports->get(i)->code == code){
            QMessageBox *msg = new QMessageBox(QMessageBox::Information, "Airport already exists!", "An airport with the same name or code already exists, please try again.", QMessageBox::Ok, this, Qt::Popup);
            msg->setWindowModality(Qt::NonModal);
            msg->setDefaultButton(QMessageBox::Ok);
            msg->exec();
            return;
        }
    }
    map->airports->add(new Airport(name, code, QPoint(0, 0), map->parentWidget()));
    map->airports->end()->absolutepos = QPoint(labelposx, labelposy);
    map->airports->end()->show();
    map->update();
    ui->NameLine->setText("");
    ui->CodeLine->setText("");
    ui->PosXLine->setText("");
    ui->PosYLine->setText("");
    ui->AirportsBox->addItem(map->airports->end()->name);
    if(!changed && loaded)
        changed = true;
}

void MainWindow::on_AddOk_clicked()
{
    if(currentAirport == 0){
        QMessageBox *msg = new QMessageBox(QMessageBox::Information, "There is no airport to add!", "If you want to add a new airport through the controls, use the \"Add New Airpor\" button instead.", QMessageBox::Ok, this, Qt::Popup);
        msg->setWindowModality(Qt::NonModal);
        msg->setDefaultButton(QMessageBox::Ok);
        msg->exec();
        return;
    }
    QString name = ui->NameLine->text();
    QString code = ui->CodeLine->text();
    if(name.isEmpty() || code.isEmpty()){
        QMessageBox *msg = new QMessageBox(QMessageBox::Information, "Information missing!", "In order to add airports you need a name and a code.", QMessageBox::Ok, this, Qt::Popup);
        msg->setWindowModality(Qt::NonModal);
        msg->setDefaultButton(QMessageBox::Ok);
        msg->exec();
        return;
    }
    if(ui->PosXLine->text().isEmpty() || ui->PosYLine->text().isEmpty()){
        QMessageBox *msg = new QMessageBox(QMessageBox::Information, "Information missing!", "In order to add airports you need a its position on the map.", QMessageBox::Ok, this, Qt::Popup);
        msg->setWindowModality(Qt::NonModal);
        msg->setDefaultButton(QMessageBox::Ok);
        msg->exec();
        return;
    }
    QRegExp re("\\d*");
    if(!re.exactMatch(ui->PosXLine->text()) || !re.exactMatch(ui->PosYLine->text())){
        QMessageBox *msg = new QMessageBox(QMessageBox::Information, "Invalid Information!", "Coordinates need to be valid numbers.", QMessageBox::Ok, this, Qt::Popup);
        msg->setWindowModality(Qt::NonModal);
        msg->setDefaultButton(QMessageBox::Ok);
        msg->exec();
        return;
    }
    int labelposx = ui->PosXLine->text().toInt();
    int labelposy = ui->PosYLine->text().toInt();
    if(labelposx < 0 || labelposx > 5760 || labelposy < 0 ||labelposy > 3217){
        QMessageBox *msg = new QMessageBox(QMessageBox::Information, "Incorrect information!", "Invalid coordinates. Please input valid coordinates and try again.", QMessageBox::Ok, this, Qt::Popup);
        msg->setWindowModality(Qt::NonModal);
        msg->setDefaultButton(QMessageBox::Ok);
        msg->exec();
        return;
    }
    for(int i = 0; i < map->airports->size(); i++){
        if(map->airports->get(i)->name == name || map->airports->get(i)->code == code){
            QMessageBox *msg = new QMessageBox(QMessageBox::Information, "Airport already exists!", "An airport with the same name or code already exists, please try again.", QMessageBox::Ok, this, Qt::Popup);
            msg->setWindowModality(Qt::NonModal);
            msg->setDefaultButton(QMessageBox::Ok);
            msg->exec();
            return;
        }
    }
    currentAirport->name = name;
    currentAirport->code = code;
    currentAirport->absolutepos = QPoint(labelposx, labelposy);
    map->update();
    ui->NameLine->setText("");
    ui->CodeLine->setText("");
    ui->PosXLine->setText("");
    ui->PosYLine->setText("");
    ui->AddOk->setEnabled(false);
    ui->newAirportOk->setEnabled(true);
    currentAirport = 0;
    ui->AirportsBox->addItem(map->airports->end()->name);
    if(!changed && loaded)
        changed = true;
}
void MainWindow::on_AirportsBox_currentIndexChanged(int index)
{
    if(ui->AddOk->isEnabled()){
        ui->AirportsBox->setCurrentIndex(0);
        return;
    }
    if(index == 0){
        currentAirport = 0;
        ui->NameLine->setText("");
        ui->CodeLine->setText("");
        ui->PosXLine->setText("");
        ui->PosYLine->setText("");
        ui->newAirportOk->setEnabled(true);
        ui->SaveChangesOk->setEnabled(false);
        ui->EditRelationsOk->setEnabled(false);
        ui->RemovePortOk->setEnabled(false);
        return;
    }
    QString currentString = ui->AirportsBox->itemText(index);
    for(int i = 0; i < map->airports->size(); i++){
        if(map->airports->get(i)->name == currentString){
            currentAirport = map->airports->get(i);
            ui->NameLine->setText(currentAirport->name);
            ui->CodeLine->setText(currentAirport->code);
            ui->PosXLine->setText(QString::number(currentAirport->absolutepos.x()));
            ui->PosYLine->setText(QString::number(currentAirport->absolutepos.y()));
            ui->SaveChangesOk->setEnabled(true);
            ui->EditRelationsOk->setEnabled(true);
            ui->RemovePortOk->setEnabled(true);
            ui->newAirportOk->setEnabled(false);
        }
    }
}

void MainWindow::on_SaveChangesOk_clicked()
{
    if(currentAirport == 0){
        QMessageBox *msg = new QMessageBox(QMessageBox::Information, "There is no airport being editted!", "No airport is being worked on, you can't save any changes!.", QMessageBox::Ok, this, Qt::Popup);
        msg->setWindowModality(Qt::NonModal);
        msg->setDefaultButton(QMessageBox::Ok);
        msg->exec();
        return;
    }
    QString name = ui->NameLine->text();
    QString code = ui->CodeLine->text();
    if(name.isEmpty() || code.isEmpty()){
        QMessageBox *msg = new QMessageBox(QMessageBox::Information, "Information missing!", "Please insert a valid name and code.", QMessageBox::Ok, this, Qt::Popup);
        msg->setWindowModality(Qt::NonModal);
        msg->setDefaultButton(QMessageBox::Ok);
        msg->exec();
        return;
    }
    if(ui->PosXLine->text().isEmpty() || ui->PosYLine->text().isEmpty()){
        QMessageBox *msg = new QMessageBox(QMessageBox::Information, "Information missing!", "Please insert valid coordinates.", QMessageBox::Ok, this, Qt::Popup);
        msg->setWindowModality(Qt::NonModal);
        msg->setDefaultButton(QMessageBox::Ok);
        msg->exec();
        return;
    }
    QRegExp re("\\d*");
    if(!re.exactMatch(ui->PosXLine->text()) || !re.exactMatch(ui->PosYLine->text())){
        QMessageBox *msg = new QMessageBox(QMessageBox::Information, "Invalid Information!", "Coordinates need to be valid numbers.", QMessageBox::Ok, this, Qt::Popup);
        msg->setWindowModality(Qt::NonModal);
        msg->setDefaultButton(QMessageBox::Ok);
        msg->exec();
        return;
    }
    int labelposx = ui->PosXLine->text().toInt();
    int labelposy = ui->PosYLine->text().toInt();
    if(labelposx < 0 || labelposx > 5760 || labelposy < 0 ||labelposy > 3217){
        QMessageBox *msg = new QMessageBox(QMessageBox::Information, "Incorrect information!", "Invalid coordinates. Please input valid coordinates and try again.", QMessageBox::Ok, this, Qt::Popup);
        msg->setWindowModality(Qt::NonModal);
        msg->setDefaultButton(QMessageBox::Ok);
        msg->exec();
        return;
    }
    for(int i = 0; i < map->airports->size(); i++){
        if(map->airports->get(i)->name == name || map->airports->get(i)->code == code){
            if(currentAirport == map->airports->get(i))
                continue;
            QMessageBox *msg = new QMessageBox(QMessageBox::Information, "Airport already exists!", "An airport with the same name or code already exists, please try again.", QMessageBox::Ok, this, Qt::Popup);
            msg->setWindowModality(Qt::NonModal);
            msg->setDefaultButton(QMessageBox::Ok);
            msg->exec();
            return;
        }
    }
    currentAirport->name = name;
    currentAirport->code = code;
    currentAirport->absolutepos = QPoint(labelposx, labelposy);
    map->update();
    ui->AirportsBox->setItemText(ui->AirportsBox->currentIndex(), currentAirport->name);
    ui->AirportsBox->setCurrentIndex(0);
    currentAirport = 0;
    ui->NameLine->setText("");
    ui->CodeLine->setText("");
    ui->PosXLine->setText("");
    ui->PosYLine->setText("");
    ui->SaveChangesOk->setEnabled(false);
    ui->EditRelationsOk->setEnabled(false);
    ui->RemovePortOk->setEnabled(false);
    ui->newAirportOk->setEnabled(true);
    if(!changed && loaded)
        changed = true;
}

void MainWindow::on_EditRelationsOk_clicked()
{
    RelationsManager *manager = new RelationsManager(this);
    manager->mainwindow = this;
    manager->indexOfCurrent = map->airports->indexOf(currentAirport);
    manager->loadLists();
    manager->show();
}

void MainWindow::on_RemovePortOk_clicked()
{
    QMessageBox *msg = new QMessageBox(QMessageBox::Question, "Are you sure?", "If you remove this airport, any relations other airports might have with it will also be removed. Proceed?", QMessageBox::Yes | QMessageBox::No, this, Qt::Popup);
    msg->setWindowModality(Qt::NonModal);
    msg->setDefaultButton(QMessageBox::Yes);
    int reply = msg->exec();
    if(reply == QMessageBox::No)
        return;
    for(int i = 0; i < map->airports->size(); i++){
        if(map->airports->get(i) == currentAirport){
            for(int j = 0; j < map->airports->size(); j++){
                if(map->airports->isAdjacent(j, i))
                    map->airports->removeEdge(j, i);
            }
            map->airports->remove(i);
            break;
        }
    }
    delete currentAirport;
    currentAirport = 0;
    int curr = ui->AirportsBox->currentIndex();
    ui->AirportsBox->setCurrentIndex(0);
    ui->AirportsBox->removeItem(curr);
    map->update();
    if(!changed && loaded)
        changed = true;
}

bool MainWindow::isEditting()
{
    return (ui->SaveChangesOk->isEnabled() || ui->EditRelationsOk->isEnabled() || ui->RemovePortOk->isEnabled());
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(changed){
        QMessageBox *msg = new QMessageBox(QMessageBox::Question, "Save Changes?", "Would you like to save the changes made to the Airline's Database?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, this, Qt::Popup);
        msg->setWindowModality(Qt::NonModal);
        msg->setDefaultButton(QMessageBox::Yes);
        int reply = msg->exec();
        if(reply == QMessageBox::Cancel)
            event->ignore();
        else if(reply == QMessageBox::Yes)
            saveXML(XMLPath);
    }
}

void MainWindow::openXML(QString path)
{
    if(path.isEmpty())
        return;
    if(map->airports->size() != 0)
        return;
    QFile f(path);
    f.open(QIODevice::ReadOnly | QIODevice::Text);
    QDomDocument doc;
    doc.setContent(&f);
    QDomElement root = doc.firstChildElement();
    QDomNodeList ports = root.elementsByTagName("Airport");
    for(int i = 0; i < ports.count(); i++){
        if(ports.at(i).isElement()){
            QDomElement curr = ports.at(i).toElement();
            map->airports->add(new Airport(curr.attribute("Name"), curr.attribute("Code"), QPoint(0, 0), map->parentWidget()));
            map->airports->end()->absolutepos = QPoint(curr.attribute("AbsoluteX").toInt(), curr.attribute("AbsoluteY").toInt());
            map->airports->end()->show();
            map->update();
        }
    }
    for(int i = 0; i < ports.count(); i++){
        if(ports.at(i).isElement()){
            QDomElement curr = ports.at(i).toElement();
            QDomNodeList rels = curr.elementsByTagName("Relation");
            for(int j = 0; j < rels.count(); j++){
                if(rels.at(j).isElement()){
                    QDomElement currRel = rels.at(j).toElement();
                    int from;
                    int to;
                    for(int m = 0; m < map->airports->size(); m++){
                        if(map->airports->get(m)->code == currRel.attribute("From")){
                            from = m;
                        }
                        if(map->airports->get(m)->code == currRel.attribute("To")){
                            to = m;
                        }
                    }
                    map->airports->addEdge(from, to, currRel.attribute("Price").toInt());
                }
            }
            map->update();
        }
    }
    f.close();
    for(int i = 0; i < map->airports->size(); i++){
        ui->AirportsBox->addItem(map->airports->get(i)->name);
    }
}

void MainWindow::saveXML(QString path)
{
    if(path.isEmpty())
        return;
    QDomDocument doc;
    QDomElement root = doc.createElement("Airports");
    doc.appendChild(root);
    for(int i = 0; i < map->airports->size(); i++){
        if(map->airports->get(i)->code == "Default" && map->airports->get(i)->name == "Default")
            continue;
        QDomElement curr = doc.createElement("Airport");
        curr.setAttribute("Code", map->airports->get(i)->code);
        curr.setAttribute("Name", map->airports->get(i)->name);
        curr.setAttribute("AbsoluteX", map->airports->get(i)->absolutepos.x());
        curr.setAttribute("AbsoluteY", map->airports->get(i)->absolutepos.y());
        root.appendChild(curr);
        for(int j = 0; j < map->airports->size(); j++){
            if(map->airports->get(j)->code == "Default" && map->airports->get(j)->name == "Default")
                continue;
            if(map->airports->isAdjacent(i,j)){
                QDomElement currRel = doc.createElement("Relation");
                currRel.setAttribute("From", map->airports->get(i)->code);
                currRel.setAttribute("To", map->airports->get(j)->code);
                currRel.setAttribute("Price", QString::number(map->airports->adjacencyValue(i, j)));
                curr.appendChild(currRel);
            }
        }
    }
    QFile f(path);
    f.open(QIODevice::ReadWrite | QIODevice::Text);
    f.resize(0);
    QTextStream stream(&f);
    stream << doc.toString();
    f.close();
}

void MainWindow::on_actionBack_to_Airlines_triggered()
{
    if(changed){
        QMessageBox *msg = new QMessageBox(QMessageBox::Question, "Save Changes?", "Would you like to save the changes made to the Airline's Database?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, this, Qt::Popup);
        msg->setWindowModality(Qt::NonModal);
        msg->setDefaultButton(QMessageBox::Yes);
        int reply = msg->exec();
        if(reply == QMessageBox::Cancel)
            return;
        else if(reply == QMessageBox::Yes)
            saveXML(XMLPath);
        changed = false;
        //go back to airlines selection code here
    }else{
        //go back to airlines selection code here
    }
}
