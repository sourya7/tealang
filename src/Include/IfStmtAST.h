#ifndef T_IF_STMT_H
#define T_IF_STMT_H

#include "NodeAST.h"
class SeqAST;
enum class NodeType;

class IfStmtAST : public NodeAST {
private:
    SNodeAST elseBlk;
    SNodeAST elifBlk;
public:
    IfStmtAST(SNodeAST c, SNodeAST ib) : NodeAST(NodeType::IFSTMT,c,ib) {};
    void SetElseBlk(SNodeAST elb) { elseBlk = elb; }
    void GenerateIR(SIRBuilder builder);
};

#endif
