#include <string>
#include "ForStmtAst.h"
#include "IrBuilder.h"
#include "WordToken.h"

/*
 * What would the vm do? 
 * for stmts are while in disguise. While we have a next element, go on
 * 
 */
void ForStmtAst::generateIr(SIrBuilder b) {
  auto forChild = std::make_shared<IrBuilder>(b);
  left_->generateIr(forChild);

  std::string varName = GUARD_CAST<WordToken *>(ident_.get())->getValue();
  forChild->declVar(varName);
  forChild->storeValue(varName);
  forChild->loadValue(varName);
  forChild->callMethod("next");

  auto forBlk = std::make_shared<IrBuilder>(forChild);
  forBlk->loadValue(varName);
  forBlk->callMethod("get");
  forBlk->declVar(varName);
  forBlk->storeValue(varName);
  right_->generateIr(forBlk);

  auto fakeBlk = std::make_shared<IrBuilder>(forChild);
  fakeBlk->breakFlow();

  forChild->condJump(forBlk, fakeBlk);
  b->declWhile(forChild);
}

