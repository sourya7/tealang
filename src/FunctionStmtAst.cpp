#include "FunctionStmtAst.h"
#include "WordToken.h"
#include "IrBuilder.h"
#include "SeqAst.h"
#include "ParamAst.h"

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
void FunctionStmtAst::generateIr(SIrBuilder b) {
  auto paramAst = GUARD_CAST<ParamAst *>(left_.get());
  b->declVar(paramAst->getName());
  auto child = std::make_shared<IrBuilder>(b);
  VecSNodeAst params = paramAst->getParams();
  for (auto p : params) {
    child->declVar(GUARD_CAST<WordToken *>(p.get())->value_);
    child->storeValue(GUARD_CAST<WordToken *>(p.get())->value_);
  }
  right_->generateIr(child);
  b->declFunc(isInit_, paramAst->getName(), paramAst->getCount(), child);
}
