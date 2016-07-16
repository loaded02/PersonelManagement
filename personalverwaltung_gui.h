#ifndef PERSONALVERWALTUNG_GUI_H
#define PERSONALVERWALTUNG_GUI_H

#include <QMainWindow>
#include <QVector>
#include <QString>
#include <QCloseEvent>
#include <addmitarbeiter_gui.h>
#include <showmitarbeiter_gui.h>
#include <editmitarbeiter_gui.h>
#include <personalverwaltung.h>

class ShowMitarbeiter_GUI;

namespace Ui {
class Personalverwaltung_GUI;
}

class Personalverwaltung_GUI : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Personalverwaltung_GUI(QWidget *parent = 0);
    ~Personalverwaltung_GUI();

public slots:
    void addMitarbeiter();
    void showMitarbeiter();
    void editMitarbeiter();
    void delMitarbeiter();
    void abfrage();
    void closeEvent(QCloseEvent * event) {
        event->ignore();
        QMessageBox msgbox(this);
        msgbox.setWindowTitle("Datensatz speichern?");
        msgbox.setText("Der aktuelle Datensatz wird gespeichert.");
        msgbox.setInformativeText("Wollen Sie die Aenderungen uebernehmen?");
        msgbox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
        msgbox.setDefaultButton(QMessageBox::Save);
        int ret = msgbox.exec();
        switch (ret) {
        case QMessageBox::Cancel : event->accept();
            break;
        case QMessageBox::Save : spezPVerw.listeSpeichern();
            event->accept();
            break;
        default : event->accept();
        }
    }

private:
    Ui::Personalverwaltung_GUI *ui;
    AddMitarbeiter_GUI* neuerMitarbeiter;
    ShowMitarbeiter_GUI* showGUI;
    EditMitarbeiter_GUI* editGUI;
    Personalverwaltung spezPVerw;
};

#endif // PERSONALVERWALTUNG_GUI_H
