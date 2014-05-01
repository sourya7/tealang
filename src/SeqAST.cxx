
#include "Debug.h"
#include "SeqAST.h"


SeqAST* SeqAST::AddSeq(NodeAST* n) {
    left = n;
    SeqAST* rs = new SeqAST(this);
    right = rs;
    return rs;
}

void SeqAST::GenerateIR(IRBuilder* builder){
    if(left != nullptr) left->GenerateIR(builder);
    if(right != nullptr) right ->GenerateIR(builder);
}

