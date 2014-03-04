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
    admincp = new AdminCP();
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
        admincp->show();
        this->close();
    }else{
        QMessageBox *msg = new QMessageBox(QMessageBox::Information, "Incorrect username or password!", "Please check your login details and try again.", QMessageBox::Ok, this, Qt::Popup);
        //msg->setWindowModality(Qt::NonModal);
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
