
#include "Debug.h"
#include "SeqAST.h"


SSeqAST SeqAST::AddSeq(SNodeAST n) {
    left = n;
    auto rs = make_shared<SeqAST>(this);
    right = rs;
    return rs;
}

void SeqAST::GenerateIR(SIRBuilder builder){
    if(left.get() != nullptr) left->GenerateIR(builder);
    if(right.get() != nullptr) right ->GenerateIR(builder);
}

