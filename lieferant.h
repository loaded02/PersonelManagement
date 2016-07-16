#ifndef LIEFERANT_H
#define LIEFERANT_H

#include<cstdlib>
#include <QString>
#include "bankverbindung.h"

class Lieferant
{
public:
    Lieferant(QString name, Bankverbindung bank)                //Konstruktor
        :name(name),bankverbindung(bank){}
    virtual ~Lieferant() {}                                             //Destruktor
    enum Beurteilung{Sehr_gut, Gut, Befriedigend, Ausreichend, Mangelhaft};
    void beurteilen(Beurteilung urteil) {
        beurteilung  = urteil;
    }
    QString getBeurteilung() {
        switch(beurteilung) {
        case 0 : return "Sehr gut";
            break;
        case 1  : return "Gut";
            break;
        case 2 : return "Befriedigend";
            break;
        case 3 : return "Ausreichend";
            break;
        case 4 : return "Mangelhaft";
            break;
        default: return "Nicht bewertet";
        }
    }

    void setBeurteilung(string modus) {
        if (modus == "Sehr gut")
            beurteilung = Lieferant::Sehr_gut;
        if (modus == "Gut")
            beurteilung = Lieferant::Gut;
        if (modus == "Befriedigend")
            beurteilung = Lieferant::Befriedigend;
        if (modus == "Ausreichend")
            beurteilung = Lieferant::Ausreichend;
        if (modus == "Mangelhaft")
            beurteilung = Lieferant::Mangelhaft;
    }

private:
    QString name;
    Bankverbindung bankverbindung;
    Beurteilung beurteilung;
};

#endif // LIEFERANT_H
