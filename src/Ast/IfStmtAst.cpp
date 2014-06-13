#include "IfStmtAst.h"
#include "Debug.h"
#include "IrBuilder.h"

void IfStmtAst::generateIr(SIrBuilder builder) {
  auto ifBlkBuild = std::make_shared<IrBuilder>(builder);

  left_->generateIr(builder);     // build the expression
  right_->generateIr(ifBlkBuild); // build the ifblock

  // If the last expressoin evals to true, jump to the child
  if (elseBlk.get() == nullptr)
    builder->condJump(ifBlkBuild);
  else {
    auto elBlkBuild = std::make_shared<IrBuilder>(builder);
    elseBlk->generateIr(elBlkBuild);
    builder->condJump(ifBlkBuild, elBlkBuild);
  }
}
