#ifndef T_PARAMAST_H
#define T_PARAMAST_H
#include "NodeAst.h"
class ParamAst : public NodeAst {
private:
  VecSNodeAst params_;
  std::string name_;

public:
  ParamAst() : NodeAst(NodeType::PARAM) {}
  void addParam(std::string s, SNodeAst node) {
    name_ += s;
    if (node != nullptr)
      params_.push_back(node);
  }
  void addParam(std::string s) { name_ += s; }
  std::string getName() { return name_; }
  int getCount() { return params_.size(); }
  VecSNodeAst getParams() { return params_; }
};
#endif
