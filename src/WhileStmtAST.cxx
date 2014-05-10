#include "WhileStmtAST.h"
#include "WordTok.h"
#include "IRBuilder.h"
#include "SeqAST.h"
#include "ParamAST.h"

void WhileStmtAST::GenerateIR(SIRBuilder b){
    auto exprChild = make_shared<IRBuilder>(b);
    left->GenerateIR(exprChild);
    auto bodyChild = make_shared<IRBuilder>(b);
    right->GenerateIR(bodyChild);
    b->DeclWhile(exprChild, bodyChild);
}

