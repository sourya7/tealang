#ifndef T_EXPR_H
#define T_EXPR_H

#include "NodeAst.h"

class ExprAst : public NodeAst {
private:
  VecSToken expr_;

public:
  ExprAst(VecSToken e) : NodeAst(NodeType::EXPR), expr_(e) {}
  void generateIr(SIrBuilder builder);
};

#endif
