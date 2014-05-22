#include "ClassStmtAST.h"
#include "IRBuilder.h"
#include "WordTok.h"

/*
 * var obj = [Animal init] --> CallMethod('Animal', 'init')
 * [Animal staticFunc]     --> CallMethod('Animal', 'staticFunc')
 * [Animal method]         --> CallMethod('
 * [obj method]            --> CallMethod('obj', 'method')
 * [obj method]        --> CallMethod('obj', 'invalid')
 * [invalid method]    --> CallMethod('invalid', 'invalid')
 *
 */
void ClassStmtAST::GenerateIR(SIRBuilder b) {
  auto wt = DYN_GC_CAST<WordTok>(left);

  // forward reference to the class
  b->DeclVar(wt->value);

  auto child = MakeShared<IRBuilder>(b);
  right->GenerateIR(child);
  b->DeclClass(wt->value, child);
}
