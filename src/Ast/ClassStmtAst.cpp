#include "Ast/ClassStmtAst.h"
#include "IrBuilder.h"
#include "WordToken.h"

/*
 * var obj = [Animal init] --> CallMethod('Animal', 'init')
 * [Animal staticFunc]     --> CallMethod('Animal', 'staticFunc')
 * [Animal method]         --> CallMethod('
 * [obj method]            --> CallMethod('obj', 'method')
 * [obj method]        --> CallMethod('obj', 'invalid')
 * [invalid method]    --> CallMethod('invalid', 'invalid')
 *
 */
void ClassStmtAst::generateIr(SIrBuilder b) {
  auto wt = std::dynamic_pointer_cast<WordToken>(left_);

  // forward reference to the class
  b->declVar(wt->getValue());
  auto child = std::make_shared<IrBuilder>(b);
  if(isa_.size() > 0) child->declClassIsa(isa_);
  right_->generateIr(child);
  b->declClass(wt->getValue(), child);
}
