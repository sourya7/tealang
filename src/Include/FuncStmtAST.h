#ifndef T_FUNCSTMTAST_H
#define T_FUNCSTMTAST_H

#include "NodeAST.h"
class IRBuilder;
class FuncStmtAST : public NodeAST{ 
    NodeAST* obj;
public:
    FuncStmtAST(NodeAST* p,NodeAST* b) : NodeAST(NodeType::FSTMT,p,b){}
    void GenerateIR(IRBuilder* b);
};

#endif
