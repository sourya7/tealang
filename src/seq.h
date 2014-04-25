
#ifndef T_SEQ_H
#define T_SEQ_H

#include "node.h"

class Seq : public Node {
private:
    Node* parent = nullptr;
public:
    Seq() : Node(NodeType::SEQ) {}
    Seq(Node* p) : Seq() { parent = p; }
    Seq* AddSeq(Node* n) {
        left = n;
        Seq* rs = new Seq(this);
        right = rs;
        return rs;
    }

    void Display(int level){
        if(left) Node::Display(level);
    }
};

#endif
