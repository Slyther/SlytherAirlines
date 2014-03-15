#include "logindg.h"
#include "ui_logindg.h"
#include "mainmenu.h"
#include <QMessageBox>

LoginDg::LoginDg(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginDg)
{
    ui->setupUi(this);
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    this->setWindowTitle("Administration Panel - Login");
    this->setFixedSize(this->width(), this->height());
    manager = new AirlineManager();
}

LoginDg::~LoginDg()
{
    delete ui;
}

void LoginDg::on_buttonBox_accepted()
{
    if(ui->lineEdit->text().toLower() == QString("Slyther").toLower() && ui->lineEdit_2->text().toLower() == QString("test").toLower()){
        this->parentMenu->close();
        ui->lineEdit->setText("");
        ui->lineEdit_2->setText("");
        manager->show();
        manager->setWindowIcon(this->windowIcon());
        manager->parentMenu = this->parentMenu;
        this->close();
    }else{
        QMessageBox *msg = new QMessageBox(QMessageBox::Information, "Incorrect username or password!", "Please check your login details and try again.", QMessageBox::Ok, this, Qt::Popup);
        msg->setDefaultButton(QMessageBox::Ok);
        msg->exec();
    }
}

void LoginDg::on_buttonBox_rejected()
{
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    this->close();
}

void LoginDg::show()
{
    QMainWindow::show();
    this->setWindowIcon(this->parentMenu->windowIcon());
}
