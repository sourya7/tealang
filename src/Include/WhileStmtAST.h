#ifndef T_WHILESTMTAST_H
#define T_WHILESTMTAST_H

#include "NodeAST.h"
class IRBuilder;
class WhileStmtAST : public NodeAST{ 
    NodeAST* obj;
public:
    WhileStmtAST(NodeAST* p,NodeAST* b) : NodeAST(NodeType::WSTMT,p,b){}
    void GenerateIR(IRBuilder* b);
};

#endif
