#ifndef T_EXPR_H
#define T_EXPR_H

#include "NodeAST.h"
class Token;
class IRBuilder;
enum class Tags;
enum class NodeType;

typedef GV<Token*>::Vector GCVecTokPtr;
class ExprAST : public NodeAST
{
private:
    GCVecTokPtr expr;
public:
    ExprAST(GCVecTokPtr e) : NodeAST(NodeType::EXPR), expr(e) {}
    void GenerateIR(IRBuilder* builder);
};

#endif
