#ifndef T_LISTAST_H
#define T_LISTAST_H

#include "NodeAST.h"

class IRBuilder;
class ListAST : public NodeAST {
private:
  vector<shared_ptr<NodeAST>>_container;
public:
  ListAST() : NodeAST(NodeType::SEQ) {}
  void AddPair(SNodeAST l, SNodeAST r);
  void GenerateIR(SIRBuilder builder);
};

#endif
