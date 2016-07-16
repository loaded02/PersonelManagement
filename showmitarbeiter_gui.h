/*
Die ModelListe darf auf keinen fall sortiert werden. Dann stimmt der agegriffene und übergeben Index nicht mehr!!!
*/

#ifndef SHOWMITARBEITER_GUI_H
#define SHOWMITARBEITER_GUI_H

#include <QDialog>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QMenu>
#include <personalverwaltung.h>
#include <editmitarbeiter_gui.h>
#include <bewertung_gui.h>
#include <QDebug>
#include <algorithm>

namespace Ui {
class ShowMitarbeiter_GUI;
}

class ShowMitarbeiter_GUI : public QDialog
{
    Q_OBJECT
    
public:
    explicit ShowMitarbeiter_GUI(Personalverwaltung* tmp, QWidget *parent = 0);
    ~ShowMitarbeiter_GUI();
    
private slots:
    void on_treeView_customContextMenuRequested(const QPoint &pos);
    void editMitarbeiter();
    void bewerteMitarbeiter();
    void refreshTreeview();
    void sucheMitarbeiter();
    double relAbstand(QString a, QString b);  //SuchAlgorithmus

    void on_treeView_doubleClicked(const QModelIndex &index);

private:
    Ui::ShowMitarbeiter_GUI *ui;
    Personalverwaltung* aktuell;
    EditMitarbeiter_GUI* editGUI;
    Bewertung_GUI* bewGUI;
    QStandardItemModel* mymodel;
};

#endif // SHOWMITARBEITER_GUI_H
