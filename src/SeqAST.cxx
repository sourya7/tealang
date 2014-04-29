
#include "Debug.h"
#include "SeqAST.h"


SeqAST* SeqAST::AddSeq(NodeAST* n) {
    left = n;
    SeqAST* rs = new SeqAST(this);
    right = rs;
    return rs;
}

void SeqAST::Display(int level){
    if(left) NodeAST::Display(level);
}

void SeqAST::GenerateIR(){
    DEBUG("SeqAST::GenerateIR()");

    if(left != nullptr) left->GenerateIR();
    if(right != nullptr) right ->GenerateIR();
}

