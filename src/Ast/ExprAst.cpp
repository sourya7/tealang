#include "IrBuilder.h"
#include "Ast/ExprAst.h"
#include "WordToken.h"
#include "Debug.h"
#include "OpToken.h"
#include "Ast/CallAst.h"
#include "Ast/ListAst.h"
#include "Object.h"

void ExprAst::generateIr(SIrBuilder builder) {
  for (auto t : expr_) {
    if (t->getTag() == Tags::OP) {
      auto op = GUARD_CAST<OpToken *>(t.get());
      builder->performOp(op->getValue());
    } else if (t->getTag() == Tags::BSQO) {
      auto call = GUARD_CAST<CallAst *>(t->getLeft().get());
      call->generateIr(builder);
    } else if (t->getTag() == Tags::ID) {
      auto wt = GUARD_CAST<WordToken *>(t.get());
      builder->loadValue(wt->getValue());
    } else if (t->getTag() == Tags::BCUO) {
      auto list = GUARD_CAST<ListAst *>(t->getLeft().get());
      list->generateIr(builder);
    } else {
      auto o = Object::fromToken(t.get());
      builder->loadConst(o);
    }
  }
}
