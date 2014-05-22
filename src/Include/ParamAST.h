#ifndef T_PARAMAST_H
#define T_PARAMAST_H
#include "NodeAST.h"
class ParamAST : public NodeAST {
private:
  VecSNodeAST params;
  string name;

public:
  ParamAST() : NodeAST(NodeType::PARAM) {}
  void AddParam(string s, SNodeAST n) {
    name += s;
    if (n != nullptr)
      params.push_back(n);
  }
  string GetName() { return name; }
  int GetCount() { return params.size(); }
  VecSNodeAST GetParams() { return params; }
};
#endif
