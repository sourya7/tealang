#ifndef T_CALLAST_H
#define T_CALLAST_H
#include "NodeAST.h"
class IRBuilder;
class CallAST : public NodeAST {
private:
public:
    CallAST() : NodeAST(NodeType::CALL) {}
    void GenerateIR(IRBuilder* builder);
};
#endif

