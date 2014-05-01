
#ifndef T_SEQ_H
#define T_SEQ_H

#include "NodeAST.h"

class IRBuilder;
class SeqAST : public NodeAST {
private:
    NodeAST* parent = nullptr;
public:
    SeqAST() : NodeAST(NodeType::SEQ) {}
    SeqAST(NodeAST* p) : SeqAST() { parent = p; }
    SeqAST* AddSeq(NodeAST* n);
    void GenerateIR(IRBuilder* builder);
};

#endif
