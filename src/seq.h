
#ifndef T_SEQ_H
#define T_SEQ_H

#include "node.h"

class Seq : public Node {
private:
    Node* parent;
    Node* next;
public:
    Seq(Node* p, Node* l, Node* r) : Node(l,r), parent(p) {}
    Seq(Node* p) : parent(p) {}
    Seq() {}
};

#endif
