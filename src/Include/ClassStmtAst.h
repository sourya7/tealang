#ifndef T_CLS_STMT_H
#define T_CLS_STMT_H

#include "NodeAst.h"

class ClassStmtAst : public NodeAst {
public:
  ClassStmtAst(SNodeAst n, SNodeAst b) : NodeAst(NodeType::CLASS, n, b) {};
  void generateIr(SIrBuilder builder);
};

#endif
