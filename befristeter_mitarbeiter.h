#ifndef BEFRISTETER_MITARBEITER_H
#define BEFRISTETER_MITARBEITER_H

#include <QString>
#include <QDate>
#include <mitarbeiter.h>

class Befristeter_Mitarbeiter : public Mitarbeiter {
public:
    Befristeter_Mitarbeiter(const int &id, const QString &vname, const QString &nname, const QDate &start, const Bankverbindung &bank, const QDate &ende)
        : Mitarbeiter(id, vname, nname, start, bank),enddatum(ende){
    }

    virtual ~Befristeter_Mitarbeiter() {}

    void setEnddatum(QDate neuEnd) {
        enddatum = neuEnd;
    }

    virtual bool istFirmenwagenBerechtigt() {
        return false;
    }

    QDate getEnddatum() {
        return enddatum;
    }

private:
    QDate enddatum;
};

#endif // BEFRISTETER_MITARBEITER_H
