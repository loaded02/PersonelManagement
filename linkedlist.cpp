#include "linkedlist.h"
#include <stdexcept>
using namespace std;

LinkedList::LinkedList() {
    root = NULL;
    cursor = NULL;
}

//sucht Einfuegestelle nach ID aufsteigend
Node* LinkedList::insertPos(Mitarbeiter *data) {
    this->reset();
    //Liste hat mind 2 Eintraege
    if (cursor && cursor->GetNextNode()) {
        //Es wird nach dem cursor eingefuegt. Also suche bis folgendes Objekt groesser ist. Dann fuege nach jetzigem ein.
        while (cursor->GetNextNode()->GetData()->getMitarbeiterID() < data->getMitarbeiterID()) {
            this->advance();
            if (this->isAtEnd()) {
                return cursor;
            }
        }
    }
    //Liste hat nur 1 Eintrag
    if (cursor) {
        if (cursor->GetData()->getMitarbeiterID() > data->getMitarbeiterID()) {
            //fuege vor cursor ein

        }
    }
    return cursor;
}

void LinkedList::insertNode(Mitarbeiter* data) {

    Node* node = new Node(data); // erzeuge neuen Knoten

    if (root == NULL) { // Leere Liste
        root = node;
    } else { //Liste nicht leer
        if (this->root->GetData()->getMitarbeiterID() > data->getMitarbeiterID()) { //erster Eintrag hat groessere ID
            node->SetNextNode(root);
            root->SetPreviousNode(node);
            //setze neuen root
            root = node;
        }
        else { //erster eintrag hat kleinere ID
            //setze cursor auf Einfuegestelle nach ID sortiert
            cursor = this->insertPos(data);

            node->SetPreviousNode(cursor);
            node->SetNextNode(cursor->GetNextNode());
            // nextNode wird initialisiert mit Nachfolger des Cursor-Zeiger
            // es wird also NACH dem aktuellen Element eingefügt
            if (cursor->GetNextNode() != NULL) { // Positionszeiger hat einen Nachfolger
                cursor->GetNextNode()->SetPreviousNode(node); //Urspruenglicher Nachfolger erhaeelt
                //neuen Knoten als Vorgaenger
            }
            cursor->SetNextNode(node);
        }
    }
    cursor = node; // Positionszeiger zeigt nun auf das neue Element
    //    cout << "Eintrag '" << data->getNachname().toStdString() << "' eingefuegt" << endl;
}

void LinkedList::deleteNode() {
    Node* tmpPrevious; // temporaere Variablen, fuer den Fall, dass der
    Node* tmpNext; // zu loeschende Knoten in der Mitte der Liste ist

    if (root == NULL) {
        // Liste leer, nichts zu loeschen
        throw underflow_error("Versuch aus leerer Liste zu loeschen");
    } else {
        if (cursor->GetPreviousNode() == NULL) {
            if (cursor->GetNextNode() == NULL) {
                // Fall 1: Die Liste besteht nur aus einem einzigen Knoten
                // Knoten loeschen, Speicher freigeben,Zeiger root und cursor loeschen
                delete cursor;
                root = 0;
                cursor = 0;
            } else {
                // Fall 2: Die Liste besteht aus mehreren Knoten .
                // Der Root-Knoten wird jetzt geloescht und der Speicherplatz
                // wiederfreigegeben

                // Zeiger auf den naechsten Knoten setzen
                cursor = cursor->GetNextNode();
                delete (root);

                // Cursor-Knoten ist jetzt erster Knoten: Vorgaenger auf NULL setzen:
                cursor->SetPreviousNode(NULL);

                // Neuen root-Knoten setzen:
                root = cursor;
            }
        } else { //cursor.getPrevious() == NULL)
            if (cursor->GetNextNode() == NULL) {
                // Fall 3: Die Liste besteht aus mehreren Knoten .
                // Der letzte Knoten wird geloescht und der Speicherplatz
                // fuer diesen Knoten wird wieder freigegeben

                // cursor-Knoten auf den vorherigen Knoten setzen
                tmpPrevious = cursor->GetPreviousNode();

                delete cursor;
                cursor = tmpPrevious;

                cursor->SetNextNode(NULL);

            } else {//cursor−>GetNext() == NULL)
                // Fall 4: Die Liste besteht aus mehreren Knoten.
                // Es wird weder der erste noch der letzte Knoten geloescht.

                // Die Adresse des vorhergehenden Knotens in tmpPrevious sichern,
                // und die Adresse des naechsten Knotens in tmpNext sichern.

                tmpPrevious = cursor->GetPreviousNode();
                tmpNext = cursor->GetNextNode();

                // Den aktuellen Knoten loeschen
                delete cursor;

                // Die Knoten tmpPrevious und tmpNext verketten
                tmpPrevious->SetNextNode(tmpNext);
                tmpNext->SetPreviousNode(tmpPrevious);

                // Den Zeiger auf das Element vor dem alten Knoten setzen
                cursor = tmpPrevious;
            }
        }
    }
    return;
}

//nach ID suchen
Node* LinkedList::suchen(Mitarbeiter* data) {
    this->reset();
    while (cursor->GetData()->getMitarbeiterID() != data->getMitarbeiterID()) {
        if (cursor->GetNextNode()) {
        cursor = cursor->GetNextNode();
        }
        else {
//            cout << "Am Ende." << endl;
            return 0;
        }
    }
    return cursor;
}
