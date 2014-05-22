#ifndef T_CLS_STMT_H
#define T_CLS_STMT_H

#include "NodeAST.h"

class ClassStmtAST : public NodeAST {
public:
  ClassStmtAST(SNodeAST n, SNodeAST b) : NodeAST(NodeType::CLASS, n, b) {};
  void GenerateIR(SIRBuilder builder);
};

#endif
