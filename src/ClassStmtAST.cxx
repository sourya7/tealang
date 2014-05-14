#include "ClassStmtAST.h"
#include "IRBuilder.h"
#include "WordTok.h"

void ClassStmtAST::GenerateIR(SIRBuilder b) {
    assert(false);
    auto wt = DYN_GC_CAST<WordTok>(left);

    //forward reference to the class
    b->DeclVar(wt->value);

    auto child = MakeShared<IRBuilder>(b);
    right->GenerateIR(child);
    b->DeclClass(wt->value, child);
}

