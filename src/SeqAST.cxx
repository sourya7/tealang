
#include "Debug.h"
#include "SeqAST.h"


SSeqAST SeqAST::AddSeq(SNodeAST n) {
    left = n;
    auto rs = MakeShared<SeqAST>(this);
    right = rs;
    return rs;
}

void SeqAST::GenerateIR(SIRBuilder builder){
    if(POINTER_VAL(left) != nullptr) left->GenerateIR(builder);
    if(POINTER_VAL(right) != nullptr) right ->GenerateIR(builder);
}

