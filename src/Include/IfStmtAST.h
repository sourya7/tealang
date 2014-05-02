#ifndef T_IF_STMT_H
#define T_IF_STMT_H

#include "NodeAST.h"
class SeqAST;
enum class NodeType;

class IfStmtAST : public NodeAST {
private:
    NodeAST* elseBlk = nullptr;
    NodeAST* elifBlk = nullptr;
public:
    IfStmtAST(NodeAST* c, NodeAST* ib) : NodeAST(NodeType::IFSTMT,c,ib) {};
    void SetElseBlk(NodeAST* elb) { elseBlk = elb; }
    void GenerateIR(IRBuilder* builder);
};

#endif
