#include "showmitarbeiter_gui.h"
#include "ui_showmitarbeiter_gui.h"

ShowMitarbeiter_GUI::ShowMitarbeiter_GUI(Personalverwaltung* tmp, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowMitarbeiter_GUI),aktuell(tmp)
{
    ui->setupUi(this);
    connect(ui->closeButton,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->searchButton,SIGNAL(clicked()),this,SLOT(sucheMitarbeiter()));
    //fill tree view
    mymodel = new QStandardItemModel(0,8); //0 rows 8 colls
    mymodel->setHorizontalHeaderItem(0,new QStandardItem(QString("Mitarbeiter ID")));
    mymodel->setHorizontalHeaderItem(1,new QStandardItem(QString("Nachname")));
    mymodel->setHorizontalHeaderItem(2,new QStandardItem(QString("Vorname")));
    mymodel->setHorizontalHeaderItem(3,new QStandardItem(QString("Startdatum")));
    mymodel->setHorizontalHeaderItem(4,new QStandardItem(QString("Adresse")));
    mymodel->setHorizontalHeaderItem(5,new QStandardItem(QString("Bankverbindung")));
    mymodel->setHorizontalHeaderItem(6,new QStandardItem(QString("Beurteilung")));
    mymodel->setHorizontalHeaderItem(7,new QStandardItem(QString("Firmenwagen")));

    for (int i=0; i<aktuell->getSize(); i++) {
        if (aktuell->getMitarbeiter(i)->getStatus() == "Aktiv") {
            QList<QStandardItem*>* row = new QList<QStandardItem*>();
            QStandardItem* item;
            for (int j=0; j<8; j++) {
                item = new QStandardItem();
                item->setEditable(0);
                row->append(item);
            }
            (*row)[0]->setText(QString("%1").arg(QString::number(aktuell->getMitarbeiter(i)->getMitarbeiterID())));
            (*row)[1]->setText(aktuell->getMitarbeiter(i)->getNachname());
            (*row)[2]->setText(aktuell->getMitarbeiter(i)->getVorname());
            (*row)[3]->setText(aktuell->getMitarbeiter(i)->getStartdatum().toString());
            (*row)[4]->setText(aktuell->getMitarbeiter(i)->getMitarbeiter_adr().strasse + " " + aktuell->getMitarbeiter(i)->getMitarbeiter_adr().hausnummer
                               + ", " + aktuell->getMitarbeiter(i)->getMitarbeiter_adr().plz + " " + aktuell->getMitarbeiter(i)->getMitarbeiter_adr().stadt);
            (*row)[5]->setText(aktuell->getMitarbeiter(i)->getKonto()->getBankname() + ", " +
                               aktuell->getMitarbeiter(i)->getKonto()->getBLZ() + ", " + aktuell->getMitarbeiter(i)->getKonto()->getKontonr());
            Freier_Mitarbeiter* test = dynamic_cast<Freier_Mitarbeiter*> (aktuell->getMitarbeiter(i));
            if (test) {
//                static_cast<Freier_Mitarbeiter*> (test);
                (*row)[6]->setText(test->getBeurteilung());
            }
            QString berechtigt;
            if (aktuell->getMitarbeiter(i)->istFirmenwagenBerechtigt())
                berechtigt = "Ja";
            else
                berechtigt = "Nein";
            (*row)[7]->setText(berechtigt);
            mymodel->appendRow(*row);
        }
    }
    ui->treeView->setModel(this->mymodel);
    //context menu
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);
//    connect(ui->treeView,SIGNAL(customContextMenuRequested(const QPoint&)),this,SLOT(on_treeView_customContextMenuRequested(const QPoint&)));
    connect(ui->actionMitarbeiterAendern,SIGNAL(triggered()),this,SLOT(editMitarbeiter()));
    connect(ui->actionMitarbeiterBewerten,SIGNAL(triggered()),this,SLOT(bewerteMitarbeiter()));
    connect(ui->clearButton,SIGNAL(clicked()),this,SLOT(refreshTreeview()));
}

void ShowMitarbeiter_GUI::refreshTreeview() {
    ui->searchEdit->clear();
    mymodel->removeRows(0,mymodel->rowCount());

    for (int i=0; i<aktuell->getSize(); i++) {
        if (aktuell->getMitarbeiter(i)->getStatus() == "Aktiv") {
            QList<QStandardItem*>* row = new QList<QStandardItem*>();
            QStandardItem* item;
            for (int j=0; j<8; j++) {
                item = new QStandardItem();
                item->setEditable(0);
                row->append(item);
            }
            (*row)[0]->setText(QString("%1").arg(QString::number(aktuell->getMitarbeiter(i)->getMitarbeiterID())));
            (*row)[1]->setText(aktuell->getMitarbeiter(i)->getNachname());
            (*row)[2]->setText(aktuell->getMitarbeiter(i)->getVorname());
            (*row)[3]->setText(aktuell->getMitarbeiter(i)->getStartdatum().toString());
            (*row)[4]->setText(aktuell->getMitarbeiter(i)->getMitarbeiter_adr().strasse + " " + aktuell->getMitarbeiter(i)->getMitarbeiter_adr().hausnummer
                               + ", " + aktuell->getMitarbeiter(i)->getMitarbeiter_adr().plz + " " + aktuell->getMitarbeiter(i)->getMitarbeiter_adr().stadt);
            (*row)[5]->setText(aktuell->getMitarbeiter(i)->getKonto()->getBankname() + ", " +
                               aktuell->getMitarbeiter(i)->getKonto()->getBLZ() + ", " + aktuell->getMitarbeiter(i)->getKonto()->getKontonr());
            Freier_Mitarbeiter* test = dynamic_cast<Freier_Mitarbeiter*> (aktuell->getMitarbeiter(i));
            if (test) {
//                static_cast<Freier_Mitarbeiter*> (test);
                (*row)[6]->setText(test->getBeurteilung());
            }
            QString berechtigt;
            if (aktuell->getMitarbeiter(i)->istFirmenwagenBerechtigt())
                berechtigt = "Ja";
            else
                berechtigt = "Nein";
            (*row)[7]->setText(berechtigt);
            mymodel->appendRow(*row);
        }
    }
}

ShowMitarbeiter_GUI::~ShowMitarbeiter_GUI()
{
    delete ui;
    delete mymodel;
}

void ShowMitarbeiter_GUI::on_treeView_customContextMenuRequested(const QPoint &pos)
{
    QPoint globalPos = ui->treeView->mapToGlobal(pos);
    QMenu myMenu;
    int index;
    QModelIndexList list = ui->treeView->selectionModel()->selectedIndexes();
    if (list.size() == 0) {
        //nichts ausgewaehlt
        index = -1;
    } else {
        //etwas ausgewaehlt
        index = list.at(0).row();
        myMenu.addAction(ui->actionMitarbeiterAendern);
        //Test auf Freier_Mitarbeiter
        Freier_Mitarbeiter* test = dynamic_cast<Freier_Mitarbeiter*> (aktuell->getMitarbeiter(index));
        if (test) {
        myMenu.addAction(ui->actionMitarbeiterBewerten);
        }
        QAction* selectedItem = myMenu.exec(globalPos);
    //    if (selectedItem) { //Sprung erfolgt ueber Signal/Slot

    //    }
    }
}

void ShowMitarbeiter_GUI::editMitarbeiter() {
    //id auf markierten Mitarbeiter setzen
    int index;
    QModelIndexList list = ui->treeView->selectionModel()->selectedIndexes();
    if (list.size() == 0) {
        //nichts ausgewaehlt
        index = -1;
    } else {
        //etwas ausgewaehlt
        index = list.at(0).row();               //index ist Eintragnr in Liste und nicht die id!!! Deswegen Listen nicht sortieren.
    }
    editGUI = new EditMitarbeiter_GUI(aktuell, index, this);
    editGUI->setAttribute(Qt::WA_DeleteOnClose,true);
    if (editGUI->exec()) {
    this->refreshTreeview();
    }
}

void ShowMitarbeiter_GUI::bewerteMitarbeiter() {
    //id auf markierten Mitarbeiter setzen
    int index;
    QModelIndexList list = ui->treeView->selectionModel()->selectedIndexes();
    if (list.size() == 0) {
        //nichts ausgewaehlt
        index = -1;
    } else {
        //etwas ausgewaehlt
        index = list.at(0).row();
    }
    bewGUI = new Bewertung_GUI(aktuell,index,this);
    if (bewGUI->exec()) {
    this->refreshTreeview();
    }
    delete bewGUI;
}

void ShowMitarbeiter_GUI::on_treeView_doubleClicked(const QModelIndex &indexx)
{
    //id auf markierten Mitarbeiter setzen
    int index;
    QModelIndexList list = ui->treeView->selectionModel()->selectedIndexes();
    if (list.size() == 0) {
        //nichts ausgewaehlt
        index = -1;
    } else {
        //etwas ausgewaehlt
        index = list.at(0).row();
    }
    editGUI = new EditMitarbeiter_GUI(aktuell,index,this);
    editGUI->setAttribute(Qt::WA_DeleteOnClose,true);
    if (editGUI->exec()) {
    this->refreshTreeview();
    }
}

void ShowMitarbeiter_GUI::sucheMitarbeiter() {
    mymodel->removeRows(0,mymodel->rowCount());
    for (int i=0; i<aktuell->getSize(); i++) {
        if (this->relAbstand(aktuell->getMitarbeiter(i)->getNachname(),ui->searchEdit->text()) <= 0.3) {        //Abweichung von Suchstring
            QList<QStandardItem*>* row = new QList<QStandardItem*>();
            QStandardItem* item;
            for (int j=0; j<8; j++) {
                item = new QStandardItem();
                item->setEditable(0);
                row->append(item);
            }
            (*row)[0]->setText(QString("%1").arg(QString::number(aktuell->getMitarbeiter(i)->getMitarbeiterID())));
            (*row)[1]->setText(aktuell->getMitarbeiter(i)->getNachname());
            (*row)[2]->setText(aktuell->getMitarbeiter(i)->getVorname());
            (*row)[3]->setText(aktuell->getMitarbeiter(i)->getStartdatum().toString());
            (*row)[4]->setText(aktuell->getMitarbeiter(i)->getMitarbeiter_adr().strasse + " " + aktuell->getMitarbeiter(i)->getMitarbeiter_adr().hausnummer
                               + ", " + aktuell->getMitarbeiter(i)->getMitarbeiter_adr().plz + " " + aktuell->getMitarbeiter(i)->getMitarbeiter_adr().stadt);
            (*row)[5]->setText(aktuell->getMitarbeiter(i)->getKonto()->getBankname() + ", " +
                               aktuell->getMitarbeiter(i)->getKonto()->getBLZ() + ", " + aktuell->getMitarbeiter(i)->getKonto()->getKontonr());
            Freier_Mitarbeiter* test = dynamic_cast<Freier_Mitarbeiter*> (aktuell->getMitarbeiter(i));
            if (test) {
                (*row)[6]->setText(test->getBeurteilung());
            }
            QString berechtigt;
            if (aktuell->getMitarbeiter(i)->istFirmenwagenBerechtigt())
                berechtigt = "Ja";
            else
                berechtigt = "Nein";
            (*row)[7]->setText(berechtigt);
            mymodel->appendRow(*row);
        }
    }
}

double ShowMitarbeiter_GUI::relAbstand(QString a, QString b) {
        int matrix[a.size()+1][b.size()+1];
        int zahl;
        matrix[0][0] = 0;
        for (int i=1; i<=a.size(); i++) {
            matrix[i][0] = i;
        }
        for (int j=1; j<=b.size(); j++) {
            matrix[0][j] = j;
        }
        for (int i = 1; i<=a.size(); i++) {
            for (int j = 1; j<=b.size(); j++) {
                if (a.at(i-1) == b.at(j-1)) { //if ai == bj
                    zahl = matrix[i-1][j-1];
                }
                else {
                    zahl = matrix[i-1][j-1]+1;
                }
                matrix[i][j] = min(zahl,min(matrix[i][j-1]+1,matrix[i-1][j]+1));
            }
        }
        return matrix[a.size()][b.size()] / (double)(a.size() + b.size());
    }

