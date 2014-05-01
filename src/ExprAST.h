#ifndef T_EXPR_H
#define T_EXPR_H

#include <vector>
#include "NodeAST.h"
class Token;
class IRBuilder;
enum class Tags;
enum class NodeType;

class ExprAST : public NodeAST
{
private:
    std::vector<Token*> expr;
public:
    ExprAST(std::vector<Token*> e) : NodeAST(NodeType::EXPR), expr(e) {}
    void GenerateIR(IRBuilder* builder);
};

#endif
