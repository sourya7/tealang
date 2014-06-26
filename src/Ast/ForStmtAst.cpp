#include <string>
#include "Ast/ForStmtAst.h"
#include "IrBuilder.h"
#include "WordToken.h"

/*
 * What would the vm do?
 * for stmts are while in disguise. While we have a next element, go on
 *
 */
void ForStmtAst::generateIr(SIrBuilder b) {
  //using [0-9]_varname is safe as we cannot have variables that begin with numbers
  //it can be used for internal purposes. 
  //TODO, try to find a way without these anyway as we don't want to pollute the global
  //namespace unless absolutely necessary

  std::string varName = GUARD_CAST<WordToken *>(ident_.get())->getValue();
  auto forChild = std::make_shared<IrBuilder>(b);
  left_->generateIr(b);
  b->callMethod("__iter__");
  // TODO we could probably use some kind of "declTemp" which can be destroyed
  // after use.his function will allow us to create tmp vars with unique name.
  // Currently this will fail when we have some kind of threading functionality
  b->declVar("0_" + varName);
  b->storeValue("0_" + varName);

  forChild->loadValue("0_" + varName);
  forChild->callMethod("next");

  auto forBlk = std::make_shared<IrBuilder>(forChild);
  forBlk->loadValue("0_" + varName);
  forBlk->callMethod("get");
  forBlk->declVar(varName);
  forBlk->storeValue(varName);
  right_->generateIr(forBlk);

  auto fakeBlk = std::make_shared<IrBuilder>(forChild);
  fakeBlk->breakFlow();

  forChild->condJump(forBlk, fakeBlk);
  b->declWhile(forChild);
}
