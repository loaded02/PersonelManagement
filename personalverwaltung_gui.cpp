#include "personalverwaltung_gui.h"
#include "ui_personalverwaltung_gui.h"

Personalverwaltung_GUI::Personalverwaltung_GUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Personalverwaltung_GUI)
{
    ui->setupUi(this);
    connect(ui->actionProgramm_beenden,SIGNAL(triggered()),this,SLOT(close()));
    connect(ui->actionMitarbeiter_anlegen,SIGNAL(triggered()),this,SLOT(addMitarbeiter()));
    connect(ui->actionPersonal_uebersicht,SIGNAL(triggered()),this,SLOT(showMitarbeiter()));
    connect(ui->actionMitarbeiter_aendern,SIGNAL(triggered()),this,SLOT(editMitarbeiter()));
    connect(ui->actionMitarbeiter_Austritt,SIGNAL(triggered()),this,SLOT(delMitarbeiter()));
    connect(ui->actionListe_speichern,SIGNAL(triggered()),this,SLOT(abfrage()));
    //spezPVerw.mitarbeiterAufnehmen("Max","Mustermann",QDate(2014,01,01),QDate(2014,01,01),Bankverbindung(),"Festangestellter");
}

Personalverwaltung_GUI::~Personalverwaltung_GUI()
{
    delete ui;
}

void Personalverwaltung_GUI::addMitarbeiter() {
    neuerMitarbeiter = new AddMitarbeiter_GUI(&spezPVerw, this);
    neuerMitarbeiter->setModal(1);
    neuerMitarbeiter->setAttribute(Qt::WA_DeleteOnClose,true);
    neuerMitarbeiter->show();
}

void Personalverwaltung_GUI::delMitarbeiter() {
    neuerMitarbeiter = new AddMitarbeiter_GUI(&spezPVerw, this, "del");
    neuerMitarbeiter->setModal(1);
    neuerMitarbeiter->setAttribute(Qt::WA_DeleteOnClose,true);                      //Destruktor
    neuerMitarbeiter->show();
}

void Personalverwaltung_GUI::showMitarbeiter() {
    showGUI = new ShowMitarbeiter_GUI(&spezPVerw);
    showGUI->setModal(1);
    showGUI->setAttribute(Qt::WA_DeleteOnClose,true);                      //Destruktor
    showGUI->show();
}

void Personalverwaltung_GUI::editMitarbeiter() {
    editGUI = new EditMitarbeiter_GUI(&spezPVerw, this);
    editGUI->setModal(1);
    editGUI->setAttribute(Qt::WA_DeleteOnClose,true);
    editGUI->show();
}

void Personalverwaltung_GUI::abfrage() {
    spezPVerw.listeSpeichern();
}
