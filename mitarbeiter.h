#ifndef MITARBEITER_H
#define	MITARBEITER_H

#include<cstdlib>
#include <QString>
#include <QDate>
#include "bankverbindung.h"
using namespace std;

struct Adresse {
    QString strasse;
    QString hausnummer;
    QString plz;
    QString stadt;
};

enum Status {
    Aktiv, Pensioniert, Verstorben, Ausgeschieden
};


class Mitarbeiter {
public:
    Mitarbeiter(const int &id, const QString &vname, const QString &nname, const QDate &start, const Bankverbindung &bank);      //Konstruktor
    virtual ~Mitarbeiter(){}                                                                       //Destruktor

    virtual bool istFirmenwagenBerechtigt() = 0;            //rein virtuelle Fkt

    void kuendigen() {
        this->status = Ausgeschieden;
    }
    void sterben() {
        this->status = Verstorben;
    }
    void pensionieren() {
        this->status = Pensioniert;
    }
    void reaktivieren() {
        this->status = Aktiv;
    }

    QString getStatus () {
        QString statusStr;
        switch (status) {
        case 0 : statusStr = "Aktiv";
            break;
        case 1 : statusStr = "Pensioniert";
            break;
        case 2 : statusStr = "Verstorben";
            break;
        case 3 : statusStr = "Ausgeschieden";
            break;
        default : statusStr = "Aktiv";
        }
        return statusStr;
    }

    void setStatus(string modus) {
        if (modus == "Aktiv")
            this->reaktivieren();
        if (modus == "Pensioniert")
            this->pensionieren();
        if (modus == "Verstorben")
            this->sterben();
        if (modus == "Ausgeschieden")
            this->kuendigen();
    }

    const int getMitarbeiterID() const {
        return mitarbeiterID;
    }

    QString getNachname() const {
        return nachname;
    }

    QDate getStartdatum() const {
        return startdatum;
    }

    QString getVorname() const {
        return vorname;
    }

    Adresse getMitarbeiter_adr() const {
        return mitarbeiter_adr;
    }

    void setAdresse(Adresse neu) {
        mitarbeiter_adr = neu;
    }

    Bankverbindung* getKonto() {
        return &konto;
    }

    void setBank(Bankverbindung neu) {
        konto = neu;
    }

private:
    const int mitarbeiterID;
    QString vorname, nachname;
    Adresse mitarbeiter_adr;
    QDate startdatum;
    int gehalt;
    QChar waehrung [3];
    Status status;
    Bankverbindung konto;
};

//inline QString bank_anzeigen(Mitarbeiter& arbeiter1) {
//    return bank_anzeigen(arbeiter1.getKonto());
//}

//inline void bank_aendern(Mitarbeiter& arbeiter1, QString name, QString blz, QString knr) {
//    bank_aendern(arbeiter1.getKonto(), name, blz, knr);
//}
#endif	/* MITARBEITER_H */
