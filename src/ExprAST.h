#ifndef T_EXPR_H
#define T_EXPR_H

#include "NodeAST.h"

class ExprAST : public NodeAST
{
private:
    vector<Token*> expr;
public:
    ExprAST(vector<Token*> e) : NodeAST(NodeType::EXPR), expr(e) {}
};

#endif
