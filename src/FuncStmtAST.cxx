#include "FuncStmtAST.h"
#include "WordTok.h"
#include "IRBuilder.h"
#include "SeqAST.h"
#include "ParamAST.h"

/*
 * defun bla:a andB:b
 *   var a = 2
 * endfun
 * PUSH_VAL b
 * PUSH_VAL a
 * call bla:andB:
 *
 * LOAD_VAL a
 * LOAD_VAL b
 * LOAD_CONST 2
 * STORE_VAL a
 * RETURN
 */
//TODO Handle anon functions
void FuncStmtAST::GenerateIR(SIRBuilder b){
    auto paramAST = GUARD_CAST<ParamAST*>(left.get());
    b->DeclVar(paramAST->GetName());
    auto child = make_shared<IRBuilder>(b);
    VecSNodeAST params = paramAST->GetParams();
    for(auto p : params) {
        child->DeclVar(GUARD_CAST<WordTok*>(p.get())->value);
        child->StoreValue(GUARD_CAST<WordTok*>(p.get())->value);
    }
    right->GenerateIR(child);
    b->DeclFunc(paramAST->GetName(),paramAST->GetCount(),child);
}

