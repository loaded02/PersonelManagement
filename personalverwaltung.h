#ifndef PERSONALVERWALTUNG_H
#define	PERSONALVERWALTUNG_H

#include<cstdlib>
#include<iostream>
#include<QVector>
#include <stdexcept>
#include <exception>
#include <fstream>
#include "mitarbeiter.h"
#include "festangestellter.h"
#include "befristeter_mitarbeiter.h"
#include "leitender_angestellter.h"
#include "praktikant.h"
#include <freier_mitarbeiter.h>
#include "linkedlist.h"
using namespace std;

class Personalverwaltung {
public:
    Personalverwaltung() :anzEintraege(0){this->listeEinlesen();}
    ~Personalverwaltung();
    void mitarbeiterAufnehmen(QString vname, QString nname, QDate start, QDate ende, Bankverbindung bank, QString art, int id = ++fortlaufende_nr);
    void mitarbeiterAendern(int id, Adresse neuAdr, Bankverbindung neuBank, QDate neuDate);
    void austrittMitarbeiter(int id, int mode);  
    int getSize() {
        return anzEintraege;
    }
    void listeSpeichern();
    Mitarbeiter* getMitarbeiter(int pos) {
        int i = 0;
        sortListe.reset();
        if (!sortListe.isAtEnd()) {     //wenn Liste nicht leer
        while (i < pos) {
            sortListe.advance();
            i++;
        }
        return sortListe.getNode();
        }
        else {      //Liste ist leer oder ein Eintrag
            return sortListe.getNode();
        }
    }

private:
    void listeEinlesen();
    static int fortlaufende_nr;
//    QVector<Mitarbeiter*> mitarbeiter_liste;
    LinkedList sortListe;
    int anzEintraege;
};


#endif	/* PERSONALVERWALTUNG_H */
