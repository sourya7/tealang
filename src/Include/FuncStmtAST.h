#ifndef T_FUNCSTMTAST_H
#define T_FUNCSTMTAST_H

#include "NodeAST.h"
class IRBuilder;
class FuncStmtAST : public NodeAST {
  SNodeAST obj;
  bool isInit;

public:
  FuncStmtAST(bool i, SNodeAST p, SNodeAST b)
      : NodeAST(NodeType::FSTMT, p, b), isInit(i) {}
  void GenerateIR(SIRBuilder b);
};

#endif
