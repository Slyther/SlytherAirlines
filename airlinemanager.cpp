#include "airlinemanager.h"
#include "ui_airlinemanager.h"
#include "mainmenu.h"

AirlineManager::AirlineManager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AirlineManager)
{
    ui->setupUi(this);
    dbXMLPath = "../AirlinesDB.xml";
    airlines = new TDALISTA< TDALISTA<QString>* >();
    this->setWindowTitle("Slyther's Airlines Administration Panel");
    openXML(dbXMLPath);
}

AirlineManager::~AirlineManager()
{
    delete ui;
}

void AirlineManager::closeEvent(QCloseEvent *ev)
{
    saveXML(dbXMLPath);
    parentMenu->show();
}

void AirlineManager::resizeEvent(QResizeEvent *ev)
{
    ev;
    ui->airlinesTable->setColumnWidth(0, this->size().width()-121);
}

void AirlineManager::on_addNewAirline_clicked()
{

    QString name = ui->airlineNameLine->text();
    if(name.isEmpty()){
        QMessageBox *msg = new QMessageBox(QMessageBox::Information, "Invalid Information!", "Please insert a name for the airline.", QMessageBox::Ok, this, Qt::Popup);
        msg->setWindowModality(Qt::NonModal);
        msg->setDefaultButton(QMessageBox::Ok);
        msg->exec();
        return;
    }
    QString name2 = name;
    for(int i = 0; i < name2.length(); i++){
        if(name2.at(i) == ' ')
            name2.replace(i, 1,'_');
    }
    QString path = QString("../%1.xml").arg(name2);
    for(int i = 0; i < airlines->size(); i++){
        if(airlines->get(i)->get(0) == name || airlines->get(i)->get(1) == path){
            QMessageBox *msg = new QMessageBox(QMessageBox::Information, "Invalid Information!", "An airline with the same name already exists!", QMessageBox::Ok, this, Qt::Popup);
            msg->setWindowModality(Qt::NonModal);
            msg->setDefaultButton(QMessageBox::Ok);
            msg->exec();
            return;
        }
    }
    airlines->add(new TDALISTA<QString>());
    airlines->end()->add(name);
    airlines->end()->add(path);
    updateTable();
}

void AirlineManager::on_manageAirline_clicked()
{
    if(ui->airlinesTable->selectedItems().size() == 0)
        return;
    MainWindow * wind = new MainWindow();
    int n = -1;
    for(int i = 0; i < airlines->size(); i++){
        if(ui->airlinesTable->selectedItems().at(0)->text() == airlines->get(i)->get(0))
            n = i;
    }
    if(n == -1)
        return;
    wind->XMLPath = airlines->get(n)->get(1);
    wind->setWindowIcon(this->windowIcon());
    wind->setWindowTitle(QString("%1 - Administration Panel").arg(airlines->get(n)->get(0)));
    wind->parentManager = this;
    wind->show();
    this->setVisible(false);
}

void AirlineManager::on_removeAirline_clicked()
{
    if(ui->airlinesTable->selectedItems().size() == 0)
        return;
    QMessageBox *msg = new QMessageBox(QMessageBox::Information, "Are you sure?", "Removing the airline from the list will also delete its database. Proceed anyways?", QMessageBox::Yes | QMessageBox::No, this, Qt::Popup);
    msg->setWindowModality(Qt::NonModal);
    msg->setDefaultButton(QMessageBox::Yes);
    int reply = msg->exec();
    if(reply == QMessageBox::No)
        return;
    int n = -1;
    for(int i = 0; i < airlines->size(); i++){
        if(ui->airlinesTable->selectedItems().at(0)->text() == airlines->get(i)->get(0))
            n = i;
    }
    if(n == -1)
        return;
    QFile f(airlines->get(n)->get(0));
    f.open(QIODevice::ReadWrite | QIODevice::Text);
    if(!f.remove()){
        QMessageBox *msg = new QMessageBox(QMessageBox::Information, "Error!", "There was an unknown error while deleting the database file.", QMessageBox::Ok, this, Qt::Popup);
        msg->setWindowModality(Qt::NonModal);
        msg->setDefaultButton(QMessageBox::Ok);
        msg->exec();
        return;
    }
    airlines->remove(n);
    updateTable();
}

void AirlineManager::openXML(QString path)
{
    if(path.isEmpty())
        return;
    QFile f(path);
    f.open(QIODevice::ReadOnly | QIODevice::Text);
    QDomDocument doc;
    doc.setContent(&f);
    QDomElement root = doc.firstChildElement();
    QDomNodeList lines = root.elementsByTagName("Airline");
    for(int i = 0; i < lines.count(); i++){
        if(lines.at(i).isElement()){
            QDomElement curr = lines.at(i).toElement();
            airlines->add(new TDALISTA<QString>());
            airlines->end()->add(curr.attribute("Name"));
            airlines->end()->add(curr.attribute("XMLPath"));
        }
    }
    f.close();
    updateTable();
}

void AirlineManager::saveXML(QString path)
{
    if(path.isEmpty())
        return;
    QDomDocument doc;
    QDomElement root = doc.createElement("Airlines");
    doc.appendChild(root);
    for(int i = 0; i < airlines->size(); i++){
        QDomElement curr = doc.createElement("Airline");
        curr.setAttribute("Name", airlines->get(i)->get(0));
        curr.setAttribute("XMLPath", airlines->get(i)->get(1));
        root.appendChild(curr);
    }
    QFile f(path);
    f.open(QIODevice::ReadWrite | QIODevice::Text);
    f.resize(0);
    QTextStream stream(&f);
    stream << doc.toString();
    f.close();
}

void AirlineManager::updateTable()
{
    while(ui->airlinesTable->rowCount() > 0)
        ui->airlinesTable->removeRow(0);
    for(int i = 0; i < airlines->size(); i++){
        ui->airlinesTable->insertRow(ui->airlinesTable->rowCount());
        ui->airlinesTable->setItem(ui->airlinesTable->rowCount()-1, 0, new QTableWidgetItem(airlines->get(i)->get(0)));
    }
    for(int i = 0; i < ui->airlinesTable->rowCount(); i++){
        ui->airlinesTable->setRowHeight(i, 20);
    }
    if(ui->airlinesTable->rowCount() > 0)
        ui->airlinesTable->selectRow(0);
}
