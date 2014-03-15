#include "userairlineselect.h"
#include "ui_userairlineselect.h"
#include "mainmenu.h"

UserAirlineSelect::UserAirlineSelect(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserAirlineSelect)
{
    ui->setupUi(this);
    this->setWindowTitle("Airline Selection");
    dbXMLPath = "../AirlinesDB.xml";
    airlines = new TDALISTA< TDALISTA<QString>* >();
    buttons = new TDALISTA<QPushButton*>();
    openXML(dbXMLPath);
    ui->scrollAreaWidgetContents->setLayout(new QVBoxLayout());
    ui->scrollAreaWidgetContents->layout()->setAlignment(Qt::AlignTop);
    for(int i = 0; i < airlines->size(); i++){
        buttons->add(new QPushButton(ui->scrollAreaWidgetContents));
        ui->scrollAreaWidgetContents->layout()->addWidget(buttons->end());
        buttons->end()->setText(airlines->get(i)->get(0));
        connect(buttons->get(i), SIGNAL(clicked()), this, SLOT(buttonClicked()));
    }

}
void UserAirlineSelect::show()
{
    setWindowIcon(parentMenu->windowIcon());
    if(airlines->size() == 0){
        QMessageBox *msg = new QMessageBox(QMessageBox::Information, "There are no Airlines!", "No airlines have been created. Please contact an Administrator for further support.", QMessageBox::Ok, this, Qt::Popup);
        msg->setWindowModality(Qt::NonModal);
        msg->setDefaultButton(QMessageBox::Ok);
        msg->exec();
        close();
        deleteLater();
        return;
    }
    this->parentMenu->setVisible(false);
    QMainWindow::show();
}

UserAirlineSelect::~UserAirlineSelect()
{
    delete ui;
}

void UserAirlineSelect::closeEvent(QCloseEvent *ev)
{
    this->parentMenu->show();
    this->deleteLater();
}

void UserAirlineSelect::buttonClicked()
{
    QPushButton *button = (QPushButton*)sender();
    int n = -1;
    for(int i = 0; i < buttons->size(); i++){
        if(buttons->get(i) == button){
            n = i;
            break;
        }
    }
    TicketPurchaseWindow* purchaseWindow = new TicketPurchaseWindow();
    purchaseWindow->setWindowIcon(this->windowIcon());
    purchaseWindow->setWindowTitle(QString("%1 - Ticket Purchase").arg(airlines->get(n)->get(0)));
    purchaseWindow->parentManager = this;
    purchaseWindow->XMLPath = airlines->get(n)->get(1);
    purchaseWindow->show();
    this->setVisible(false);
}

void UserAirlineSelect::openXML(QString path)
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
}
