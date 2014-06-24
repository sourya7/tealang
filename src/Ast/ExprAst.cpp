#include "IrBuilder.h"
#include "Ast/ExprAst.h"
#include "WordToken.h"
#include "Debug.h"
#include "OpToken.h"
#include "Ast/CallAst.h"
#include "Ast/ListAst.h"
#include "Object.h"
#include "Objects/StringObject.h"

void ExprAst::generateIr(SIrBuilder builder) {
  for (size_t i = 0; i < expr_.size(); i++) {
    SToken t = expr_[i];
    if (t->getTag() == Tags::OP) {
      auto op = GUARD_CAST<OpToken *>(t.get());
      builder->performOp(op->getValue());
    } else if (t->getTag() == Tags::BSQO) {
      auto call = GUARD_CAST<CallAst *>(t->getLeft().get());
      call->generateIr(builder);
    } else if (t->getTag() == Tags::ID) {
      auto wt = GUARD_CAST<WordToken *>(t.get());
      // If the next token is a 'dot' operator, we cannot dererence the value
      // now
      if ((i + 1 < expr_.size()) && expr_[i + 1]->getTag() == Tags::OP) {
        auto op = GUARD_CAST<OpToken *>(expr_[i + 1].get());
        if (op->getValue() == Opc::DOT) {
          builder->loadConst(std::make_shared<StringObject>(wt->getValue()));
          continue;
        }
      }
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
