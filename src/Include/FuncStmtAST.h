#ifndef T_FUNCSTMTAST_H
#define T_FUNCSTMTAST_H

#include "NodeAST.h"
class IRBuilder;
class FuncStmtAST : public NodeAST{ 
    SNodeAST obj;
public:
    FuncStmtAST(SNodeAST p,SNodeAST b) : NodeAST(NodeType::FSTMT,p,b){}
    void GenerateIR(SIRBuilder b);
};

#endif
