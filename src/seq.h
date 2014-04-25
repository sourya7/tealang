
#ifndef T_SEQ_H
#define T_SEQ_H

#include "node.h"

class Seq : public Node {
private:
    Node* parent;
public:
    Seq(Node* p) : parent(p) {}
    Seq() {}
    Seq* AddSeq(Node* n) {
        left = n;
        Seq* rs = new Seq(this);
        right = rs;
        return rs;
    }
};

#endif
