#include "IrBuilder.h"
#include "ExprAst.h"
#include "WordToken.h"
#include "Debug.h"
#include "OpToken.h"
#include "CallAst.h"
#include "ListAst.h"
#include "Object.h"

void ExprAst::generateIr(SIrBuilder builder) {
  for (auto t : expr_) {
    if (t->tag_ == Tags::OP) {
      auto op = GUARD_CAST<OpToken *>(t.get());
      builder->performOp(op->value_);
    } else if (t->tag_ == Tags::BSQO) {
      auto call = GUARD_CAST<CallAst *>(t->getLeft().get());
      call->generateIr(builder);
    } else if (t->tag_ == Tags::ID) {
      auto wt = GUARD_CAST<WordToken *>(t.get());
      builder->loadValue(wt->value_);
    } else if (t->tag_ == Tags::BCUO) {
      auto list = GUARD_CAST<ListAst *>(t->getLeft().get());
      list->generateIr(builder);
    } else {
      auto o = Object::fromToken(t.get());
      builder->loadConst(o);
    }
  }
}
