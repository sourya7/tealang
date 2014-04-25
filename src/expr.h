#ifndef T_EXPR_H
#define T_EXPR_H

#include "node.h"

class Expr : public Node
{
private:
    vector<Token*> expr;
public:
    Expr(vector<Token*> e) : Node(NodeType::EXPR), expr(e) {}
};

#endif
