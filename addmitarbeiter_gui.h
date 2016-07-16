#ifndef ADDMITARBEITER_GUI_H
#define ADDMITARBEITER_GUI_H

#include <QDialog>
#include <QMessageBox>
#include <personalverwaltung.h>

namespace Ui {
class AddMitarbeiter_GUI;
}

class AddMitarbeiter_GUI : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddMitarbeiter_GUI(Personalverwaltung* tmp, QWidget *parent = 0, QString type = "add");
    ~AddMitarbeiter_GUI();

    
private slots:
    void on_comboBox_currentIndexChanged(const QString &arg1);
    void setupDel();
    void changeStatus();
    void Add();
    void on_comboBox_id_activated(const QString &arg1);

    void on_dateEdit_dateChanged(const QDate &date);

private:
    Ui::AddMitarbeiter_GUI *ui;
    Personalverwaltung* aktuell;
};

#endif // ADDMITARBEITER_GUI_H
