#include <string>
#include <iostream>
#include "NodeAst.h"
#include "WordToken.h"
#include "IrBuilder.h"
#include "Debug.h"
#include "Object.h"

void NodeAst::generateIr(SIrBuilder builder) {
  switch (type_) {
  case NodeType::VAR:
    // declare the variable;
    builder->declVar(GUARD_CAST<WordToken *>(left_.get())->getValue());
    // if the right exists, call it
    if (right_.get() != nullptr)
      right_->generateIr(builder);
    break;
  case NodeType::ASSIGN:
    // eval the right node
    right_->generateIr(builder);
    // load the val into the var
    builder->storeValue(GUARD_CAST<WordToken *>(left_.get())->getValue());
    break;
  case NodeType::TOKEN: {
    // TODO, this is a hack
    auto t = GUARD_CAST<Token *>(this);
    if (t->getTag() == Tags::ID) {
      auto wt = GUARD_CAST<WordToken *>(t);
      builder->loadValue(wt->getValue());
    } else {
      builder->loadConst(Object::fromToken(t));
    }
    break;
  }
  case NodeType::RETURN: {
    if (left_.get() == nullptr)
      builder->returnNoValue();
    else {
      left_->generateIr(builder);
      builder->returnValue();
      break;
    }
  }
  case NodeType::CALL:
    assert(false && "CALL");
  case NodeType::PARAM:
    assert(false && "PARAM");
  case NodeType::IFSTMT:
    assert(false && "IFSTMT");
  case NodeType::FSTMT:
    assert(false && "FSTMT");
  case NodeType::EXPR:
    assert(false && "EXPR");
  default:
    assert(false && "This should not be called!");
  }
}
