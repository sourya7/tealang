#ifndef T_WHILESTMTAST_H
#define T_WHILESTMTAST_H
#include "NodeAst.h"

class IrBuilder;
class WhileStmtAst : public NodeAst {
  SNodeAst object_;

public:
  WhileStmtAst(SNodeAst predicate, SNodeAst block)
      : NodeAst(NodeType::WSTMT, predicate, block) {}
  void generateIr(SIrBuilder builder);
};

#endif
