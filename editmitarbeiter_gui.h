#ifndef EDITMITARBEITER_GUI_H
#define EDITMITARBEITER_GUI_H

#include <QDialog>
#include <personalverwaltung.h>

namespace Ui {
class EditMitarbeiter_GUI;
}

class EditMitarbeiter_GUI : public QDialog
{
    Q_OBJECT
    
public:
    explicit EditMitarbeiter_GUI(Personalverwaltung* tmp, QWidget *parent = 0);
    EditMitarbeiter_GUI(Personalverwaltung* tmp, int index, QWidget *parent = 0);
    ~EditMitarbeiter_GUI();
    
private slots:
    void on_comboBox_activated(const QString &arg1);
    void save_stuff();

private:
    Ui::EditMitarbeiter_GUI *ui;
    Personalverwaltung* aktuell;
};

#endif // EDITMITARBEITER_GUI_H
