#ifndef T_NODE_H
#define T_NODE_H

#include "GC.h"

class IRBuilder;
enum class NodeType {NODE, SEQ, CALL, PARAM, IFSTMT, FSTMT, ASSIGN, EXPR, TOKEN, VAR};
class NodeAST : public TGC {
protected:
    NodeAST* left = nullptr;
    NodeAST* right = nullptr; 
    NodeType type = NodeType::NODE;
public:
    NodeAST() {} 
    NodeAST(NodeType t) : type(t) {} 
    NodeAST(NodeAST* l, NodeAST* r) : left(l), right(r) {} 
    NodeAST(NodeType t, NodeAST *l, NodeAST* r) : type(t), left(l), right(r) {} 
    void SetLeft(NodeAST* l) { left = l; }
    void SetRight(NodeAST* r) { right = r; }
    virtual void GenerateIR(IRBuilder* builder);
};

#endif
