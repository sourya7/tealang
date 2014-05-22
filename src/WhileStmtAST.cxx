#include "WhileStmtAST.h"
#include "WordTok.h"
#include "IRBuilder.h"
#include "SeqAST.h"
#include "ParamAST.h"

void WhileStmtAST::GenerateIR(SIRBuilder b) {
  auto exprChild = MakeShared<IRBuilder>(b);
  left->GenerateIR(exprChild);
  auto bodyChild = MakeShared<IRBuilder>(b);
  right->GenerateIR(bodyChild);
  b->DeclWhile(exprChild, bodyChild);
}
