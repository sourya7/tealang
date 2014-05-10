#ifndef T_NODE_H
#define T_NODE_H

#include "GC.h"
#include "Debug.h"
#include <string>
using std::string;

class IRBuilder;
enum class NodeType {NODE, SEQ, CALL, PARAM, IFSTMT, FSTMT,WSTMT, ASSIGN, EXPR, TOKEN, VAR, RETURN};
class NodeAST : public TGC {
protected:
    SNodeAST left;
    SNodeAST right;
    NodeType type = NodeType::NODE;
public:
    NodeAST() {} 
    NodeAST(NodeType t) : type(t) {} 
    NodeAST(SNodeAST l, SNodeAST r) : left(l), right(r) {} 
    NodeAST(NodeType t, SNodeAST l, SNodeAST r) : type(t), left(l), right(r) {} 
    void SetLeft(SNodeAST l) { left = l; }
    void SetRight(SNodeAST r) { right = r; }
    NodeType GetType() { return type; }
    SNodeAST GetLeft() { return left; }
    SNodeAST GetRight() { return right; }
    virtual void GenerateIR(SIRBuilder builder);
};

#endif
