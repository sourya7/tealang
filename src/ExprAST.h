#ifndef T_EXPR_H
#define T_EXPR_H

#include <vector>
#include "NodeAST.h"
class Token;
enum class Tags;
enum class NodeType;

class ExprAST : public NodeAST
{
private:
    std::vector<Token*> expr;
public:
    ExprAST(std::vector<Token*> e) : NodeAST(NodeType::EXPR), expr(e) {}
    void Display(int level);
    void GenerateIR();
};

#endif
