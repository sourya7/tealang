#ifndef T_CALLAST_H
#define T_CALLAST_H
#include "NodeAst.h"
class IrBuilder;
class CallAst : public NodeAst {
private:
public:
  CallAst() : NodeAst(NodeType::CALL) {}
  void generateIr(SIrBuilder builder);
};
#endif
