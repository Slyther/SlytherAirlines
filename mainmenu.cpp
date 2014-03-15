#include "mainmenu.h"
#include "ui_mainmenu.h"

MainMenu::MainMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/programicon.png"));
    setFixedSize(this->width(), this->height());
    this->setWindowTitle("Slyther's Airlines");
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::on_AdminButton_clicked()
{
    LoginDg * dial = new LoginDg();
    dial->parentMenu = this;
    dial->show();
}

void MainMenu::on_UserButton_clicked()
{
    UserAirlineSelect * uas = new UserAirlineSelect();
    uas->parentMenu = this;
    uas->show();
}
