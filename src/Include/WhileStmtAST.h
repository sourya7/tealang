#ifndef T_WHILESTMTAST_H
#define T_WHILESTMTAST_H

#include "NodeAST.h"
class IRBuilder;
class WhileStmtAST : public NodeAST{ 
    SNodeAST obj;
public:
    WhileStmtAST(SNodeAST p,SNodeAST b) : NodeAST(NodeType::WSTMT,p,b){}
    void GenerateIR(SIRBuilder b);
};

#endif
