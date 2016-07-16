#include "addmitarbeiter_gui.h"
#include "ui_addmitarbeiter_gui.h"

AddMitarbeiter_GUI::AddMitarbeiter_GUI(Personalverwaltung* tmp, QWidget *parent, QString type) :
    QDialog(parent),
    ui(new Ui::AddMitarbeiter_GUI), aktuell(tmp)
{
    ui->setupUi(this);
    ui->comboBox->addItem("Festangestellter");
    ui->comboBox->addItem("Leitender_Angestellter");
    ui->comboBox->addItem("Befristeter_Mitarbeiter");
    ui->comboBox->addItem("Praktikant");
    ui->comboBox->addItem("Freier_Mitarbeiter");
    if (type == "del") {
        setupDel();
    }
    else {
        ui->groupBox_2->hide();
        ui->dateEdit_2->setMinimumDate(QDate(2013,11,01));
        connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(Add()));
    }
}

AddMitarbeiter_GUI::~AddMitarbeiter_GUI()
{
    delete ui;
}

void AddMitarbeiter_GUI::Add() {
    Bankverbindung tmpBank(ui->bankname->text(),ui->bankblz->text(),ui->bankknr->text());
    //Callback Fkt aus Personalverwaltung.h
    aktuell->mitarbeiterAufnehmen(ui->nameText->text(), ui->lastnameText->text(), ui->dateEdit->date(), ui->dateEdit_2->date(),
                                  tmpBank, ui->comboBox->currentText());
}

void AddMitarbeiter_GUI::setupDel() {
    //ruft bei accepted changeStatus auf
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(changeStatus()));
    this->setWindowTitle("Mitarbeiter Loeschen");
    this->resize(315,492);
    ui->groupBox_bank->hide();
    ui->groupBox_2->setEnabled(1);
    ui->comboBox->setEnabled(0);
    ui->dateEdit->setEnabled(0);
    ui->lastnameText->setEnabled(0);
    ui->nameText->setEnabled(0);
    ui->comboBox_id->setEnabled(1);
    for (int i=0; i<aktuell->getSize(); i++) {
        ui->comboBox_id->addItem(QString::number(aktuell->getMitarbeiter(i)->getMitarbeiterID()));
    }
    ui->comboBox_id->setCurrentIndex(-1);
}

void AddMitarbeiter_GUI::changeStatus() {
    QMessageBox msgbox(this);
    msgbox.setWindowTitle("SIND SIE SICHER???");
    msgbox.setText("Der Status des Mitarbeiters wird geaendert.");
    msgbox.setInformativeText("Wollen Sie die Aenderungen uebernehmen?");
    msgbox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
    msgbox.setDefaultButton(QMessageBox::Save);
    int ret = msgbox.exec();
    switch (ret) {
    case QMessageBox::Cancel : this->close();
        break;
    case QMessageBox::Save : if (ui->comboBox_id->currentIndex() != -1) {
            if (ui->radioButton_2->isChecked()) {
                //Callback nach personalverwaltung.h
                aktuell->austrittMitarbeiter(ui->comboBox_id->currentText().toInt(), 3); //3 fuer kuendigen
            }
            if (ui->radioButton_4->isChecked()) {
                aktuell->austrittMitarbeiter(ui->comboBox_id->currentText().toInt(), 2); //2 fuer sterben
            }
            if (ui->radioButton_3->isChecked()) {
                aktuell->austrittMitarbeiter(ui->comboBox_id->currentText().toInt(), 1); //1 fuer pensionieren
            }
            if (ui->radioButton->isChecked()) {
                aktuell->austrittMitarbeiter(ui->comboBox_id->currentText().toInt(), 4); //4 fuer reaktivieren
            }
            }
        break;
    default : this->close();
    }
}

void AddMitarbeiter_GUI::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if (arg1 == "Befristeter_Mitarbeiter" || arg1 == "Praktikant" || arg1 == "Freier_Mitarbeiter") {
        ui->dateEdit_2->setEnabled(1);
    }
    else {
        ui->dateEdit_2->setEnabled(0);
    }
}

void AddMitarbeiter_GUI::on_comboBox_id_activated(const QString &arg1)
{
    int i;
    for (i = 0; i<aktuell->getSize(); i++) {
        if (arg1 == QString::number(aktuell->getMitarbeiter(i)->getMitarbeiterID())) break;
    }
    ui->lastnameText->setText(aktuell->getMitarbeiter(i)->getNachname());
    ui->nameText->setText(aktuell->getMitarbeiter(i)->getVorname());
    ui->dateEdit->setDate(aktuell->getMitarbeiter(i)->getStartdatum());
    Befristeter_Mitarbeiter* test = dynamic_cast<Befristeter_Mitarbeiter*>(aktuell->getMitarbeiter(i));
    if (test) {
//        static_cast<Befristeter_Mitarbeiter*> (test);
        ui->dateEdit_2->setDate(test->getEnddatum());
    }
}

void AddMitarbeiter_GUI::on_dateEdit_dateChanged(const QDate &date)
{
    ui->dateEdit_2->setMinimumDate(date);
}
