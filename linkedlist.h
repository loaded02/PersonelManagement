#ifndef LINKEDLIST_H
#define	LINKEDLIST_H
#include "node.h"
#include <stdexcept>
#include <iostream>
using namespace std;

class LinkedList {
public:
    LinkedList();

    void insertNode(Mitarbeiter* data);

    bool isAtEnd() {
        if (cursor)
            return (cursor->GetNextNode() == NULL);
        else
            return true;
    };

    void advance() {
        if (cursor && cursor->GetNextNode()) {
            cursor->SetPreviousNode(cursor);
            cursor = cursor->GetNextNode();
//            cout << "Cursor weitergeschoben auf " << cursor << endl;
        }
//        else
//            cout << "Cursor ist schon am Ende " << endl;
    };
    void deleteNode();

    Mitarbeiter* getNode() {
        return cursor->GetData();
    };

    void reset() {
        cursor = root;
//        cout << "Cursor zurueckgesetzt auf root" << endl;
    };

    Node* suchen(Mitarbeiter* data);

    Node* insertPos(Mitarbeiter* data);

protected:
    Node* root;
    Node* cursor;
};

#endif	/* LINKEDLIST_H */
