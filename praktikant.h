#ifndef PRAKTIKANT_H
#define PRAKTIKANT_H

#include <QString>
#include <befristeter_mitarbeiter.h>

class Praktikant : public Befristeter_Mitarbeiter {
public:
    Praktikant(const int &id, const QString &vname, const QString &nname, const QDate &start, const Bankverbindung &bank, const QDate &ende)
    : Befristeter_Mitarbeiter(id, vname, nname, start, bank, ende) {
    }

    virtual ~Praktikant() {}
};


#endif // PRAKTIKANT_H
