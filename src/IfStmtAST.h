#ifndef T_IF_STMT_H
#define T_IF_STMT_H

#include "NodeAST.h"
#include "ExprAST.h"

class IfStmtAST : public NodeAST {
public:
    IfStmtAST(NodeAST* c, NodeAST* ib) : NodeAST(NodeType::IFSTMT,c,ib) {};
    void SetElseBlock(SeqAST* eb) { } 
    void SetElifBlock(SeqAST* elb) { }
};

#endif
