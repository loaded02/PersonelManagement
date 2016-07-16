#include "editmitarbeiter_gui.h"
#include "ui_editmitarbeiter_gui.h"

EditMitarbeiter_GUI::EditMitarbeiter_GUI(Personalverwaltung* tmp, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditMitarbeiter_GUI), aktuell(tmp)
{
    ui->setupUi(this);
    for (int i=0; i<aktuell->getSize(); i++) {
        ui->comboBox->addItem(QString::number(aktuell->getMitarbeiter(i)->getMitarbeiterID()));
    }
    ui->comboBox->setCurrentIndex(-1);
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(save_stuff()));
}

EditMitarbeiter_GUI::EditMitarbeiter_GUI(Personalverwaltung* tmp,int index, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditMitarbeiter_GUI), aktuell(tmp)
{
    ui->setupUi(this);
    for (int i=0; i<aktuell->getSize(); i++) {
        ui->comboBox->addItem(QString::number(aktuell->getMitarbeiter(i)->getMitarbeiterID()));
    }
    ui->comboBox->setCurrentIndex(index); //index ist Position in der Liste von ausgewaehltem Mitarbeiter
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(save_stuff()));
    if (index != -1) {
    this->on_comboBox_activated(QString::number(index+1001)); //spezifische Konstante wg fortlaufender Nummer in personalverwaltung
    }
}

EditMitarbeiter_GUI::~EditMitarbeiter_GUI()
{
    delete ui;
}

void EditMitarbeiter_GUI::on_comboBox_activated(const QString &arg1)
{
    int j;
    for (j=0; j<aktuell->getSize();j++) {
        if (QString::number(aktuell->getMitarbeiter(j)->getMitarbeiterID()) == arg1) break;          //finde Mitarbeiter zu ID
    }
                ui->lineEdit_3->setText(aktuell->getMitarbeiter(j)->getKonto()->getBankname());      //fuelle Maske
                ui->lineEdit_2->setText(aktuell->getMitarbeiter(j)->getKonto()->getBLZ());
                ui->lineEdit->setText(aktuell->getMitarbeiter(j)->getKonto()->getKontonr());
                ui->lineEdit_5->setText(aktuell->getMitarbeiter(j)->getMitarbeiter_adr().strasse);
                ui->lineEdit_6->setText(aktuell->getMitarbeiter(j)->getMitarbeiter_adr().hausnummer);
                ui->lineEdit_7->setText(aktuell->getMitarbeiter(j)->getMitarbeiter_adr().plz);
                ui->lineEdit_8->setText(aktuell->getMitarbeiter(j)->getMitarbeiter_adr().stadt);
                Befristeter_Mitarbeiter* test = dynamic_cast<Befristeter_Mitarbeiter*>(aktuell->getMitarbeiter(j));
                if (test) {
                    ui->dateEdit->show();
                    ui->label_9->show();
                    ui->dateEdit->setMinimumDate(test->getStartdatum());
                    ui->dateEdit->setDate(test->getEnddatum());

                } else {
                    ui->dateEdit->hide();
                    ui->label_9->hide();
                }
}

void EditMitarbeiter_GUI::save_stuff() {
    if (ui->comboBox->currentIndex() != -1) {
        //callback nach personalverwaltung.h
        Adresse tmp;
        Bankverbindung tmpBank(ui->lineEdit_3->text(),ui->lineEdit_2->text(),ui->lineEdit->text());
        tmp.strasse = ui->lineEdit_5->text();
        tmp.hausnummer = ui->lineEdit_6->text();
        tmp.plz = ui->lineEdit_7->text();
        tmp.stadt = ui->lineEdit_8->text();
        aktuell->mitarbeiterAendern(ui->comboBox->currentText().toInt(),tmp,tmpBank,ui->dateEdit->date());
    }
}
