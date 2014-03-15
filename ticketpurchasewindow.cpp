#include "ticketpurchasewindow.h"
#include "ui_ticketpurchasewindow.h"
#include <QtXml>
#include <QPaintEngine>
#include <QMessageBox>
#include <QDebug>
#include "userairlineselect.h"

TicketPurchaseWindow::TicketPurchaseWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TicketPurchaseWindow)
{
    ui->setupUi(this);
    labels = new TDALISTA<QLabel*>();
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
    map = new UserMap(ui->scrollAreaWidgetContents);
    map->setObjectName(QStringLiteral("Map"));
    map->setScaledContents(true);
    map->setFixedSize(this->size().width()-203, this->size().height()-40);
    ui->horizontalLayout_2->addWidget(map);
    ui->costLabel->setText("0");
    map->mainwindow = this;
    ui->AirportsBox->addItem("");
    ui->AirportsBox_2->addItem("");
    ui->AirportsBox_2->setEnabled(false);
    ui->scrollAreaWidgetContents_2->setLayout(new QVBoxLayout());
    ui->scrollAreaWidgetContents_2->layout()->setAlignment(Qt::AlignTop);
}

void TicketPurchaseWindow::show()
{
    openXML(XMLPath);
    QMainWindow::show();
}

TicketPurchaseWindow::~TicketPurchaseWindow()
{
    delete ui;
}

void TicketPurchaseWindow::resizeEvent(QResizeEvent* event)
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

void TicketPurchaseWindow::on_ZoomIn_clicked()
{
    if(map->size().width()*1.2 >= 5760 || map->size().height()*1.2 >= 3217){
        map->setFixedSize(5760, 3217);
        ui->ZoomIn->setEnabled(false);
    }else{
        map->setFixedSize(map->size() * 1.2);
    }
    ui->ZoomOut->setEnabled(true);
}

void TicketPurchaseWindow::on_ZoomOut_clicked()
{
    if(map->size().width()/1.2 <= this->size().width()-203 || map->size().height()/1.2 <= this->size().height()-40){
        map->setFixedSize(this->size().width()-203, this->size().height()-40);
        ui->ZoomOut->setEnabled(false);
    }else{
        map->setFixedSize(map->size() / 1.2);
    }
    ui->ZoomIn->setEnabled(true);
}

void TicketPurchaseWindow::closeEvent(QCloseEvent *event)
{
    parentManager->show();
    this->deleteLater();
}

void TicketPurchaseWindow::openXML(QString path)
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
        }
    }
    f.close();
    for(int i = 0; i < map->airports->size(); i++){
        ui->AirportsBox->addItem(map->airports->get(i)->name);
    }
}

void TicketPurchaseWindow::on_actionBack_to_Airlines_triggered()
{
    close();
}

void TicketPurchaseWindow::on_AirportsBox_currentIndexChanged(int index)
{
    if(index > 0)
        currentAirport = map->airports->get(index-1);
    else
        currentAirport = 0;
    ui->AirportsBox_2->setCurrentIndex(0);
    map->update();

    for(int i = ui->AirportsBox_2->count()-1; i > 0; i--){
        ui->AirportsBox_2->removeItem(i);
    }
    for(int i = 0; i < map->airports->size(); i++){
        if(i == index-1)
            continue;
        ui->AirportsBox_2->addItem(map->airports->get(i)->name);
    }
    if(index == 0){
        ui->AirportsBox_2->setEnabled(false);
    }else{
        ui->AirportsBox_2->setEnabled(true);
    }
}

void TicketPurchaseWindow::on_AirportsBox_2_currentIndexChanged(int index)
{
    map->currentPath->empty();
    for(int i = labels->size()-1; i >= 0 ; i--){
        QLabel* curr = labels->get(i);
        labels->remove(i);
        delete curr;
    }
    map->update();
    ui->costLabel->setText("0");
    if(index == 0){
        return;
    }else{
        if(index >= ui->AirportsBox->currentIndex())
            index +=1;

        map->currentPath = map->airports->path(ui->AirportsBox->currentIndex()-1, index-1);
        for(int i = 0; i < map->currentPath->size(); i++){
            map->currentPath->get(i)->show();
            labels->add(new QLabel(ui->scrollAreaWidgetContents_2));
            ui->scrollAreaWidgetContents_2->layout()->addWidget(labels->end());
            labels->end()->setText(QString("%1 - %2").arg(QString::number(i+1), map->currentPath->get(i)->name));
        }
        map->update();
        if(map->currentPath->size()>0){
            ui->costLabel->setText(QString::number(map->airports->pathWeight(ui->AirportsBox->currentIndex()-1, index-1)));
        }else{
            ui->costLabel->setText("Not Available!");
        }
    }
}
