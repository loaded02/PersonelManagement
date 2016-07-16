#ifndef NODE_H
#define	NODE_H
#include "mitarbeiter.h"
using namespace std;

class Node {
public:

    Node(Mitarbeiter* data) : data(data),previousNode(NULL),nextNode(NULL) {
    }

    ~Node() {           //eingefuegt wegen Mitarbeiterdata
        delete data;
    }

    Node* GetNextNode() const {
        return nextNode;
    }

    void SetNextNode(Node* nextNode) {
        this->nextNode = nextNode;
    }

    Node* GetPreviousNode() const {
        return previousNode;
    }

    void SetPreviousNode(Node* previousNode) {
        this->previousNode = previousNode;
    }

    Mitarbeiter* GetData() const {
        return data;
    }

    void SetData(Mitarbeiter* data) {
        this->data = data;
    }


private:
    Mitarbeiter* data;
    Node* previousNode;
    Node* nextNode;
};

#endif	/* NODE_H */

