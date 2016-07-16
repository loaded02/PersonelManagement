#include "personalverwaltung.h"

int Personalverwaltung::fortlaufende_nr = 1000;

void Personalverwaltung::mitarbeiterAufnehmen(QString vname, QString nname, QDate start, QDate ende, Bankverbindung bank, QString art, int id) {
    Mitarbeiter* tmp = NULL;
    if (art == "Festangestellter") {      
        tmp = new Festangestellter(id, vname, nname, start, bank);
    }
    if (art == "Befristeter_Mitarbeiter") {
        tmp = new Befristeter_Mitarbeiter(id, vname, nname, start, bank, ende);
    }
    if (art == "Leitender_Angestellter") {
        tmp = new Leitender_Angestellter(id, vname, nname, start, bank);
    }
    if (art == "Praktikant") {
        tmp = new Praktikant(id, vname, nname, start, bank, ende);
    }
    if (art == "Freier_Mitarbeiter") {
        tmp = new Freier_Mitarbeiter(id, vname, nname, start, bank, ende);
    }
    sortListe.insertNode(tmp);
    anzEintraege++;
}

void Personalverwaltung::mitarbeiterAendern(int id, Adresse neuAdr, Bankverbindung neuBank, QDate neuDate) {
    bool nicht_vorhanden = true;
    int i;
    for (i=0; i<this->getSize(); i++) {
        if (id == this->getMitarbeiter(i)->getMitarbeiterID()) {
            nicht_vorhanden = false;
            break;
        }
    }
    if (nicht_vorhanden) {
        // throw!! wenn keiner gefunden wird
        throw runtime_error("Mitarbeiter mit dieser ID ist nicht vorhanden!");
    }
    this->getMitarbeiter(i)->setAdresse(neuAdr);
    this->getMitarbeiter(i)->setBank(neuBank);
    Befristeter_Mitarbeiter* tmp = dynamic_cast<Befristeter_Mitarbeiter*>(this->getMitarbeiter(i));
    if (tmp) {
        tmp->setEnddatum(neuDate);
    }
}

void Personalverwaltung::austrittMitarbeiter(int id, int mode) {
    bool nicht_vorhanden = true;
    int i;
    for (i=0; i<this->getSize(); i++) {
        if (id == this->getMitarbeiter(i)->getMitarbeiterID()) {
            nicht_vorhanden = false;
            break;
        }
    }
    if (nicht_vorhanden) {
        throw runtime_error("Mitarbeiter mit dieser ID ist nicht vorhanden!");
    }
     // throw!! wenn keiner gefunden wird
    switch (mode) {
    case 1 : this->getMitarbeiter(i)->pensionieren();
        break;
    case 2 : this->getMitarbeiter(i)->sterben();
        break;
    case 3 : this->getMitarbeiter(i)->kuendigen();
        break;
    case 4 : this->getMitarbeiter(i)->reaktivieren();
        break;
    default: cout << "Status nicht moeglich\n";
    }
}

Personalverwaltung::~Personalverwaltung() {     //Destruktor
    sortListe.reset();
    for (int i=0; i<this->getSize(); i++) {
        sortListe.deleteNode();
        sortListe.advance();
    }
}

void Personalverwaltung::listeEinlesen() {
    ifstream quelle;
    string quellendateiname  = "mitarbeiter.txt";
    quelle.open(quellendateiname.c_str(), ios::in);
    if (!quelle) {
        cerr << quellendateiname << " kann nicht geoeffnet werden!\n";
        exit(-1);
    }
    char ch;
    string zeile,id,vname, nname, startdatum,bname,bnr,blz,str, hnr,plz,ort,status,enddatum,bewertung;
    size_t found;
    while (quelle.get(ch)) {
        getline(quelle,zeile);
        zeile.erase(0,1);
        found = zeile.find_first_of(';');
        id = zeile.substr(0,found);
        zeile.erase(0,found+1);
        found = zeile.find_first_of(' ');
        nname = zeile.substr(0,found);
        zeile.erase(0,found+1);
        found = zeile.find_first_of(';');
        vname = zeile.substr(0,found);
        zeile.erase(0,found+1);
        found = zeile.find_first_of(';');
        startdatum = zeile.substr(0,found);
        zeile.erase(0,found+1);
        found = zeile.find_first_of(' ');
        bname = zeile.substr(0,found);
        zeile.erase(0,found+1);
        found = zeile.find_first_of(' ');
        bnr = zeile.substr(0,found);
        zeile.erase(0,found+1);
        found = zeile.find_first_of(';');
        blz = zeile.substr(0,found);
        zeile.erase(0,found+1);
        found = zeile.find_first_of(' ');
        str = zeile.substr(0,found);
        zeile.erase(0,found+1);
        found = zeile.find_first_of(' ');
        hnr = zeile.substr(0,found);
        zeile.erase(0,found+1);
        found = zeile.find_first_of(' ');
        plz = zeile.substr(0,found);
        zeile.erase(0,found+1);
        found = zeile.find_first_of(';');
        ort = zeile.substr(0,found);
        zeile.erase(0,found+1);
        found = zeile.find_first_of(';');
        status = zeile.substr(0,found);
        zeile.erase(0,found+1);
        found = zeile.find_first_of(';');
        enddatum = zeile.substr(0,found);
        zeile.erase(0,found+1);
        found = zeile.find_first_of(';');
        bewertung = zeile.substr(0,found);
        zeile.erase(0,found+1);
            if (ch == 'L') {
                this->mitarbeiterAufnehmen(QString::fromStdString(vname), QString::fromStdString(nname),
                                           QDate::fromString(QString::fromStdString(startdatum),Qt::TextDate),QDate::fromString(QString::fromStdString(enddatum),Qt::TextDate),
                                           Bankverbindung(QString::fromStdString(bname),QString::fromStdString(blz),
                                                          QString::fromStdString(bnr)),"Leitender_Angestellter",QString::fromStdString(id).toInt());
            }
            if (ch == 'P') {
                this->mitarbeiterAufnehmen(QString::fromStdString(vname), QString::fromStdString(nname),
                                           QDate::fromString(QString::fromStdString(startdatum),Qt::TextDate),QDate::fromString(QString::fromStdString(enddatum),Qt::TextDate),
                                           Bankverbindung(QString::fromStdString(bname),QString::fromStdString(blz),
                                                          QString::fromStdString(bnr)),"Praktikant",QString::fromStdString(id).toInt());
            }
            if (ch == 'f') {
                this->mitarbeiterAufnehmen(QString::fromStdString(vname), QString::fromStdString(nname),
                                           QDate::fromString(QString::fromStdString(startdatum),Qt::TextDate),QDate::fromString(QString::fromStdString(enddatum),Qt::TextDate),
                                           Bankverbindung(QString::fromStdString(bname),QString::fromStdString(blz),
                                                          QString::fromStdString(bnr)),"Freier_Mitarbeiter",QString::fromStdString(id).toInt());
                //setzen der Beurteilung
                Freier_Mitarbeiter* tmp = static_cast<Freier_Mitarbeiter*>(sortListe.getNode());
                tmp->setBeurteilung(bewertung);
            }
            if (ch == 'B') {
                this->mitarbeiterAufnehmen(QString::fromStdString(vname), QString::fromStdString(nname),
                                           QDate::fromString(QString::fromStdString(startdatum),Qt::TextDate),QDate::fromString(QString::fromStdString(enddatum),Qt::TextDate),
                                           Bankverbindung(QString::fromStdString(bname),QString::fromStdString(blz),
                                                          QString::fromStdString(bnr)),"Befristeter_Mitarbeiter",QString::fromStdString(id).toInt());
            }
            if (ch == 'F') {
                this->mitarbeiterAufnehmen(QString::fromStdString(vname), QString::fromStdString(nname),
                                           QDate::fromString(QString::fromStdString(startdatum),Qt::TextDate),QDate::fromString(QString::fromStdString(enddatum),Qt::TextDate),
                                           Bankverbindung(QString::fromStdString(bname),QString::fromStdString(blz),
                                                          QString::fromStdString(bnr)),"Festangestellter",QString::fromStdString(id).toInt());
            }
            //setzen der Adresse und des Status
            Adresse neu;
            neu.hausnummer = QString::fromStdString(hnr);
            neu.plz = QString::fromStdString(plz);
            neu.stadt = QString::fromStdString(ort);
            neu.strasse = QString::fromStdString(str);
            sortListe.getNode()->setAdresse(neu);
            sortListe.getNode()->setStatus(status);
    }
    quelle.close();
    //id hochsetzen!!!
    int maxID = 0;
    for (int i=0; i<this->getSize(); i++) {
        if (this->getMitarbeiter(i)->getMitarbeiterID() > maxID) {
            maxID = this->getMitarbeiter(i)->getMitarbeiterID();
        }
    }
    fortlaufende_nr = maxID;
}

void Personalverwaltung::listeSpeichern() {
    ofstream ziel;
    string zieldateiname = "mitarbeiter.txt";
    ziel.open(zieldateiname.c_str(), ios::out | ios::trunc);
    if (!ziel) {
        cerr << zieldateiname << " kann nicht geoeffnet werden!\n";
        exit(-1);
    }
    for (int i=0; i<this->getSize(); i++) {
        if (dynamic_cast<Leitender_Angestellter*>(this->getMitarbeiter(i))) {
            Leitender_Angestellter* tmp  = static_cast<Leitender_Angestellter*>(this->getMitarbeiter(i));
            ziel << "L;" << QString::number(tmp->getMitarbeiterID()).toStdString() << ";" << tmp->getNachname().toStdString() << " " <<
                    tmp->getVorname().toStdString() << ";" << tmp->getStartdatum().toString(Qt::TextDate).toStdString() <<
                    ";" << tmp->getKonto()->getBankname().toStdString() << " " << tmp->getKonto()->getBLZ().toStdString() << " " <<
                    tmp->getKonto()->getKontonr().toStdString() << ";" << tmp->getMitarbeiter_adr().strasse.toStdString() << " " << tmp->getMitarbeiter_adr().hausnummer.toStdString() << " " <<
                    tmp->getMitarbeiter_adr().plz.toStdString() << " " << tmp->getMitarbeiter_adr().stadt.toStdString() << ";" << tmp->getStatus().toStdString() << endl;
            continue;
        }
        if (dynamic_cast<Praktikant*>(this->getMitarbeiter(i))) {
            Praktikant* tmp  = static_cast<Praktikant*>(this->getMitarbeiter(i));
            ziel << "P;"<< QString::number(tmp->getMitarbeiterID()).toStdString() << ";" << tmp->getNachname().toStdString() << " " <<
                    tmp->getVorname().toStdString() << ";" << tmp->getStartdatum().toString(Qt::TextDate).toStdString() <<
                    ";" << tmp->getKonto()->getBankname().toStdString() << " " << tmp->getKonto()->getBLZ().toStdString() << " " <<
                    tmp->getKonto()->getKontonr().toStdString() << ";" << tmp->getMitarbeiter_adr().strasse.toStdString() << " " << tmp->getMitarbeiter_adr().hausnummer.toStdString() << " " <<
                    tmp->getMitarbeiter_adr().plz.toStdString() << " " << tmp->getMitarbeiter_adr().stadt.toStdString() << ";" << tmp->getStatus().toStdString() << ";" <<
                    tmp->getEnddatum().toString(Qt::TextDate).toStdString() << endl;
            continue;
        }
        if (dynamic_cast<Freier_Mitarbeiter*>(this->getMitarbeiter(i))) {
            Freier_Mitarbeiter* tmp  = static_cast<Freier_Mitarbeiter*>(this->getMitarbeiter(i));
            ziel << "f;"<< QString::number(tmp->getMitarbeiterID()).toStdString() << ";" << tmp->getNachname().toStdString() << " " <<
                    tmp->getVorname().toStdString() << ";" << tmp->getStartdatum().toString(Qt::TextDate).toStdString() <<
                    ";" << tmp->getKonto()->getBankname().toStdString() << " " << tmp->getKonto()->getBLZ().toStdString() << " " <<
                    tmp->getKonto()->getKontonr().toStdString() << ";" << tmp->getMitarbeiter_adr().strasse.toStdString() << " " << tmp->getMitarbeiter_adr().hausnummer.toStdString() << " " <<
                    tmp->getMitarbeiter_adr().plz.toStdString() << " " << tmp->getMitarbeiter_adr().stadt.toStdString() << ";" << tmp->getStatus().toStdString() << ";" <<
                    tmp->getEnddatum().toString(Qt::TextDate).toStdString() << ";" << tmp->getBeurteilung().toStdString() << endl;
            continue;
        }
        if (dynamic_cast<Befristeter_Mitarbeiter*>(this->getMitarbeiter(i))) {
            Befristeter_Mitarbeiter* tmp  = static_cast<Befristeter_Mitarbeiter*>(this->getMitarbeiter(i));
            ziel << "B;"<< QString::number(tmp->getMitarbeiterID()).toStdString() << ";" << tmp->getNachname().toStdString() << " " <<
                    tmp->getVorname().toStdString() << ";" << tmp->getStartdatum().toString(Qt::TextDate).toStdString() <<
                    ";" << tmp->getKonto()->getBankname().toStdString() << " " << tmp->getKonto()->getBLZ().toStdString() << " " <<
                    tmp->getKonto()->getKontonr().toStdString() << ";" << tmp->getMitarbeiter_adr().strasse.toStdString() << " " << tmp->getMitarbeiter_adr().hausnummer.toStdString() << " " <<
                    tmp->getMitarbeiter_adr().plz.toStdString() << " " << tmp->getMitarbeiter_adr().stadt.toStdString() << ";" << tmp->getStatus().toStdString() << ";" <<
                    tmp->getEnddatum().toString(Qt::TextDate).toStdString() << endl;
            continue;
        }
        if (dynamic_cast<Festangestellter*>(this->getMitarbeiter(i))) {
            Festangestellter* tmp  = static_cast<Festangestellter*>(this->getMitarbeiter(i));
            ziel << "F;"<< QString::number(tmp->getMitarbeiterID()).toStdString() << ";" << tmp->getNachname().toStdString() << " " <<
                    tmp->getVorname().toStdString() << ";" << tmp->getStartdatum().toString(Qt::TextDate).toStdString() <<
                    ";" << tmp->getKonto()->getBankname().toStdString() << " " << tmp->getKonto()->getBLZ().toStdString() << " " <<
                    tmp->getKonto()->getKontonr().toStdString() << ";" << tmp->getMitarbeiter_adr().strasse.toStdString() << " " << tmp->getMitarbeiter_adr().hausnummer.toStdString() << " " <<
                    tmp->getMitarbeiter_adr().plz.toStdString() << " " << tmp->getMitarbeiter_adr().stadt.toStdString() << ";" << tmp->getStatus().toStdString() << endl;
            continue;
        }
    }
    ziel.close();
}

