#ifndef T_IF_STMT_H
#define T_IF_STMT_H

#include "node.h"
#include "expr.h"

class IfStmt : public Node {
public:
    IfStmt(Node* c, Node* ib) : Node(NodeType::IFSTMT,c,ib) {};

    void SetElseBlock(Seq* eb) {
    }

    void SetElifBlock(Seq* elb) {
    }
};

#endif
