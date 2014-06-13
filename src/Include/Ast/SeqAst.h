
#ifndef T_SEQ_H
#define T_SEQ_H

#include "NodeAst.h"

class SeqAst : public NodeAst {
private:
  NodeAst *parent_;

public:
  SeqAst() : NodeAst(NodeType::SEQ) {}
  SeqAst(NodeAst *parent) : SeqAst() { parent_ = parent; }
  SSeqAst addSeq(SNodeAst node);
  void generateIr(SIrBuilder builder);
};

#endif
