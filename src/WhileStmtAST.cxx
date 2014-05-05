#include "WhileStmtAST.h"
#include "WordTok.h"
#include "IRBuilder.h"
#include "SeqAST.h"
#include "ParamAST.h"

void WhileStmtAST::GenerateIR(IRBuilder* b){
    IRBuilder* exprChild = new IRBuilder(b);
    left->GenerateIR(exprChild);
    IRBuilder* bodyChild = new IRBuilder(b);
    right->GenerateIR(bodyChild);
    b->DeclWhile(exprChild, bodyChild);
}

