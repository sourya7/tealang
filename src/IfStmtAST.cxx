#include "IfStmtAST.h"
#include "Debug.h"
#include "IRBuilder.h"

void IfStmtAST::GenerateIR(SIRBuilder builder) {
  auto ifBlkBuild = MakeShared<IRBuilder>(builder);

  left->GenerateIR(builder); // build the expression
  right->GenerateIR(ifBlkBuild); // build the ifblock

  // If the last expressoin evals to true, jump to the child
  if (POINTER_VAL(elseBlk) == nullptr)
    builder->CondJump(ifBlkBuild);
  else {
    auto elBlkBuild = MakeShared<IRBuilder>(builder);
    elseBlk->GenerateIR(elBlkBuild);
    builder->CondJump(ifBlkBuild, elBlkBuild);
  }
}
