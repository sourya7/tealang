#include "WhileStmtAst.h"
#include "WordToken.h"
#include "IrBuilder.h"
#include "SeqAst.h"
#include "ParamAst.h"

/*
 * What would while do? 
 * take the whileChild and pushco
 * whileChild
 *    expression
 *    jump to body if expression is true
 *    otherwise break
 */
void WhileStmtAst::generateIr(SIrBuilder b) {
  auto whileChild = std::make_shared<IrBuilder>(b);

  auto bodyChild = std::make_shared<IrBuilder>(whileChild);
  right_->generateIr(bodyChild);
  left_->generateIr(whileChild);

  auto fakeChild = std::make_shared<IrBuilder>(whileChild);
  fakeChild->breakFlow();

  whileChild->condJump(bodyChild, fakeChild);
  b->declWhile(whileChild);
}


