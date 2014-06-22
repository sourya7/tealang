#ifndef T_NODE_H
#define T_NODE_H

#include <string>
#include "Debug.h"
#include "Common.h"

class IRBuilder;
enum class NodeType {
  NODE,
  SEQ,
  CALL,
  PARAM,
  IFSTMT,
  FSTMT,
  WSTMT,
  ASSIGN,
  EXPR,
  TOKEN,
  VAR,
  RETURN,
  BREAK,
  CLASS
};
class NodeAst {
protected:
  NodeType type_ = NodeType::NODE;
  SNodeAst left_;
  SNodeAst right_;

public:
  NodeAst() {}
  NodeAst(NodeType type) : type_(type) {}
  NodeAst(SNodeAst left, SNodeAst right) : left_(left), right_(right) {}
  NodeAst(NodeType type, SNodeAst left, SNodeAst right)
      : type_(type), left_(left), right_(right) {}
  void setLeft(SNodeAst left) { left_ = left; }
  void setRight(SNodeAst right) { right_ = right; }
  NodeType getType() { return type_; }
  SNodeAst getLeft() { return left_; }
  SNodeAst getRight() { return right_; }
  virtual void generateIr(SIrBuilder builder);
};

#endif
