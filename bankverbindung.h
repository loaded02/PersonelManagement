#ifndef BANKVERBINDUNG_H
#define BANKVERBINDUNG_H

#include <QString>

class Bankverbindung {
public:
    Bankverbindung() {}
    Bankverbindung(QString name, QString blz, QString knr)
        :bankname(name),BLZ(blz),kontonummer(knr) {}
    void ueberweisen();
    QString getBankname() {
        return bankname;
    }
    QString getBLZ() {
        return BLZ;
    }
    QString getKontonr() {
        return kontonummer;
    }

    void aendereBank(QString name, QString blz, QString knr) {
        bankname = name;
        BLZ = blz;
        kontonummer = knr;
    }
private:
    QString bankname;
    QString BLZ;
    QString kontonummer;
};

//inline QString bank_anzeigen(const Bankverbindung& bank1) {
//    return bank1.getBank();
//}

//inline void bank_aendern(Bankverbindung& bank1, QString name, QString blz, QString knr) {
//    bank1.aendereBank(name, blz, knr);
//}

#endif // BANKVERBINDUNG_H
