#ifndef LEITENDER_ANGESTELLTER_H
#define LEITENDER_ANGESTELLTER_H

#include <QString>
#include <festangestellter.h>

class Leitender_Angestellter : public Festangestellter {
public:
    Leitender_Angestellter(const int &id, const QString &vname, const QString &nname, const QDate &start, const Bankverbindung &bank)
    :Festangestellter(id, vname, nname, start, bank) {}

    virtual ~Leitender_Angestellter() {}

    virtual bool istFirmenwagenBerechtigt() {
        return true;
    }
};

#endif // LEITENDER_ANGESTELLTER_H
