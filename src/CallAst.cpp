#include "CallAst.h"
#include "ParamAst.h"
#include "IrBuilder.h"
#include "WordToken.h"

/*
 * Number of ways a function can be called
 * 1. [callA:2 andB:4]
 *    Here we are calling the function callA:andB:
 *    with the arguments [2,4]. The steps of generation
 *    are:
 *    a. Push 4 as a constant
 *    b. Push 2 as a constant
 *    c. Call "callA:andB:4"
 *
 *  2. [callA:a andB:b]
 *     We are calling the function with the variables [a,b]n
 *     We:
 *     a. Load the value of the constant b
 *     b. Load the value of the constant c
 *     c. Call "callA:andB:
 *
 *  3. [callA:(2+2) andB:b]
 *     Here, we have an expression to parse.
 *     a. Load the constant b
 *     b. Parse the expression and load its value
 *     c. Call "callA:andB:"
 *
 */
void CallAst::generateIr(SIrBuilder builder) {
  auto paramAst = GUARD_CAST<ParamAst *>(right_.get());
  VecSNodeAst params = paramAst->getParams();
  for (auto it = params.rbegin(), end = params.rend(); it != end; ++it) {
    (*it)->generateIr(builder);
  }

  if (left_.get() != nullptr) {
    // there is an object.
    if (left_->getType() == NodeType::PARAM) {
      // there is a function to generate an object
      assert(false);
      left_->generateIr(builder);
    } else {
      // its simply an id to an object
      std::string val = GUARD_CAST<WordToken *>(left_.get())->getValue();
      builder->loadValue(val);
    }
    builder->callMethod(paramAst->getName());
  } else {
    // its a simple function call
    builder->callFunc(paramAst->getName());
  }
}
