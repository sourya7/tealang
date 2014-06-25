#ifndef T_CLS_STMT_H
#define T_CLS_STMT_H

#include "NodeAst.h"

class ClassStmtAst : public NodeAst {
private:
  std::vector<std::string> isa_;
public:
  ClassStmtAst(SNodeAst n, SNodeAst b, std::vector<std::string> i)
      : NodeAst(NodeType::CLASS, n, b), isa_(i) {};
  void generateIr(SIrBuilder builder);
};

#endif
