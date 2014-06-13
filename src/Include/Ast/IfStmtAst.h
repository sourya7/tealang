#ifndef T_IF_STMT_H
#define T_IF_STMT_H

#include "NodeAst.h"
class SeqAst;
enum class NodeType;

class IfStmtAst : public NodeAst {
private:
  SNodeAst elseBlk;
  SNodeAst elifBlk;

public:
  IfStmtAst(SNodeAst c, SNodeAst ib) : NodeAst(NodeType::IFSTMT, c, ib) {};
  void setElseBlk(SNodeAst elb) { elseBlk = elb; }
  void generateIr(SIrBuilder builder);
};

#endif
