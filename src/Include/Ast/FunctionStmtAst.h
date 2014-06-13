#ifndef T_FUNCSTMTAST_H
#define T_FUNCSTMTAST_H

#include "NodeAst.h"
class FunctionStmtAst : public NodeAst {
  SNodeAst object_;
  bool isInit_;

public:
  FunctionStmtAst(bool isInit, SNodeAst parent, SNodeAst block)
      : NodeAst(NodeType::FSTMT, parent, block), isInit_(isInit) {}
  void generateIr(SIrBuilder builder);
};

#endif
