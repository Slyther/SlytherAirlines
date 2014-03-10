#ifndef RELATIONSMANAGER_H
#define RELATIONSMANAGER_H

#include <QMainWindow>
class MainWindow;
namespace Ui {
class RelationsManager;
}

class RelationsManager : public QMainWindow
{
    Q_OBJECT

public:
    explicit RelationsManager(QWidget *parent = 0);
    ~RelationsManager();
    MainWindow * mainwindow;
    int indexOfCurrent;
    void loadLists();
    void updateSizes();
    void closeEvent(QCloseEvent *ev);
    bool changed;

private slots:
    void on_AddOk_clicked();

    void on_RemoveOk_clicked();

    void on_AirportsList_clicked(const QModelIndex &index);

    void on_RelationsList_clicked(const QModelIndex &index);

private:
    Ui::RelationsManager *ui;
};

#endif // RELATIONSMANAGER_H
