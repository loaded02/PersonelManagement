#ifndef FREIER_MITARBEITER_H
#define FREIER_MITARBEITER_H

#include <lieferant.h>
#include <befristeter_mitarbeiter.h>

class Freier_Mitarbeiter : public Lieferant, public Befristeter_Mitarbeiter
{
public:
    Freier_Mitarbeiter(const int &id, const QString &vname, const QString &nname, const QDate &start, const Bankverbindung &bank, const QDate &ende) //Konstruktor
        :Lieferant(nname, bank),Befristeter_Mitarbeiter(id, vname, nname, start, bank, ende){}
    virtual ~Freier_Mitarbeiter() {}                                //Destruktor
};

#endif // FREIER_MITARBEITER_H
