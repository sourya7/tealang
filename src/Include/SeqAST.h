
#ifndef T_SEQ_H
#define T_SEQ_H

#include "NodeAST.h"

class IRBuilder;
class SeqAST : public NodeAST {
private:
  NodeAST *parent;

public:
  SeqAST() : NodeAST(NodeType::SEQ) {}
  SeqAST(NodeAST *p) : SeqAST() { parent = p; }
  SSeqAST AddSeq(SNodeAST n);
  void GenerateIR(SIRBuilder builder);
};

#endif
