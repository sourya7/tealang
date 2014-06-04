#include "WhileStmtAst.h"
#include "WordToken.h"
#include "IrBuilder.h"
#include "SeqAst.h"
#include "ParamAst.h"

void WhileStmtAst::generateIr(SIrBuilder b) {
  auto exprChild = std::make_shared<IrBuilder>(b);
  left_->generateIr(exprChild);
  auto bodyChild = std::make_shared<IrBuilder>(b);
  right_->generateIr(bodyChild);
  b->declWhile(exprChild, bodyChild);
}
