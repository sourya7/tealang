
#ifndef T_SEQ_H
#define T_SEQ_H

#include "NodeAST.h"

class SeqAST : public NodeAST {
private:
    NodeAST* parent = nullptr;
public:
    SeqAST() : NodeAST(NodeType::SEQ) {}
    SeqAST(NodeAST* p) : SeqAST() { parent = p; }
    SeqAST* AddSeq(NodeAST* n) {
        left = n;
        SeqAST* rs = new SeqAST(this);
        right = rs;
        return rs;
    }

    void Display(int level){
        if(left) NodeAST::Display(level);
    }
};

#endif
