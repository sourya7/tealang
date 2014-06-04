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
// TODO Handle anon functions
void FuncStmtAST::GenerateIR(SIRBuilder b) {
  auto paramAST = GUARD_CAST<ParamAST *>(POINTER_VAL(left));
  b->DeclVar(paramAST->GetName());
  auto child = MakeShared<IRBuilder>(b);
  VecSNodeAST params = paramAST->GetParams();
  for (auto p : params) {
    child->DeclVar(GUARD_CAST<WordTok *>(POINTER_VAL(p))->value);
    child->StoreValue(GUARD_CAST<WordTok *>(POINTER_VAL(p))->value);
  }
  right->GenerateIR(child);
  b->DeclFunc(isInit, paramAST->GetName(), paramAST->GetCount(), child);
}
