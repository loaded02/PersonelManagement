#include "mitarbeiter.h"

Mitarbeiter::Mitarbeiter(const int &id, const QString &vname, const QString &nname, const QDate &start, const Bankverbindung &bank)
    :mitarbeiterID(id), vorname(vname), nachname(nname),startdatum(start), status(Aktiv),konto(bank) {
}
