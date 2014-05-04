#ifndef T_PARAMAST_H
#define T_PARAMAST_H
#include "NodeAST.h"
typedef GV<NodeAST*>::Vector GCVecNodePtr;
class ParamAST : public NodeAST {
private:
    GCVecNodePtr params;
    string name;
public:
    ParamAST() : NodeAST(NodeType::PARAM) {}
    void AddParam(string s, NodeAST* n) { 
        name += s;
        if(n != nullptr) params.push_back(n);
    }
    string GetName(){ return name; }
    int GetCount(){ return params.size(); }
    GCVecNodePtr GetParams() { return params; }
};
#endif

