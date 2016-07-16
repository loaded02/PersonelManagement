#ifndef FESTANGESTELLTER_H
#define FESTANGESTELLTER_H

#include <QString>
#include <mitarbeiter.h>

class Festangestellter : public Mitarbeiter {
public:
    Festangestellter(const int &id, const QString &vname, const QString &nname, const QDate &start, const Bankverbindung &bank)
    :Mitarbeiter(id, vname, nname, start, bank) {}

    virtual ~Festangestellter() {}

    virtual bool istFirmenwagenBerechtigt() {
        if (this->getStartdatum().daysTo(QDate::currentDate()) >= 1095)
            return true;                        //3 Jahre nach Amtsantritt
        else
            return false;
    }
};

#endif // FESTANGESTELLTER_H
