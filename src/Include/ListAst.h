#ifndef T_LISTAST_H
#define T_LISTAST_H

#include "NodeAst.h"

class IrBuilder;
class ListAst : public NodeAst {
private:
  VecSNodeAst container_;

public:
  ListAst() : NodeAst(NodeType::SEQ) {}
  void addPair(SNodeAst l, SNodeAst r);
  void generateIr(SIrBuilder builder);
};

#endif
