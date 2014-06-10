#ifndef T_FORSTMTAST_H
#define T_FORSTMTAST_H
#include "NodeAst.h"

class IrBuilder;
class ForStmtAst : public NodeAst {
  SNodeAst ident_;
public:
  ForStmtAst(SNodeAst ident, SNodeAst iter, SNodeAst body)
      : NodeAst(NodeType::WSTMT, iter, body) {}
  void generateIr(SIrBuilder builder);
};

#endif
