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
void FuncStmtAST::GenerateIR(IRBuilder* b){
    ParamAST* paramAST = (ParamAST*)left;
    b->DeclVar(paramAST->GetName());
    IRBuilder* child = new IRBuilder(b);
    GCVecNodePtr params = paramAST->GetParams();
    for(auto p : params) {
        child->DeclVar(((WordTok*)p)->value);
        child->StoreValue(((WordTok*)p)->value);
    }
    right->GenerateIR(child);
    b->DeclFunc(paramAST->GetName(),paramAST->GetCount(),child);
}

