#ifndef T_EXPR_H
#define T_EXPR_H

#include "NodeAST.h"
class Token;
class IRBuilder;
enum class Tags;
enum class NodeType;

class ExprAST : public NodeAST {
private:
  VecSTok expr;

public:
  ExprAST(VecSTok e) : NodeAST(NodeType::EXPR), expr(e) {}
  void GenerateIR(SIRBuilder builder);
};

#endif
