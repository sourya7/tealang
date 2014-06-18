#ifndef T_CODEOBJECT_H
#define T_CODEOBJECT_H

#include <string>
#include "Debug.h"
#include "Object.h"
#include "OpCode.h"

enum class BlockType {
  FUNCTION,
  CLASS,
  WHILE,
  IF,
  EXPR
};

class CodeObject;

class CodeObject {
private:
  // variables in the codeobject scope
  SVecString ids_;
  // value for those vars
  SVecSObject vals_;
  // constants in the codeobject scope
  SVecSObject consts_;
  // opcodes for this codeobject
  SVecOp opcode_;
  SVecSCodeObject children_;
  SCodeObject parent_ = nullptr;
  SObject object_ = nullptr;
  BlockType type_ = BlockType::EXPR;

public:
  CodeObject(SCodeObject parent) : CodeObject() { parent_ = parent; }

  CodeObject(const CodeObject &rhs) {
    parent_ = rhs.parent_;
    children_ = rhs.children_;
    opcode_ = rhs.opcode_;
    consts_ = rhs.consts_;
    vals_ = std::make_shared<VecSObject>(*rhs.vals_);
    ids_ = rhs.ids_;
    object_ = rhs.object_;
    type_ = rhs.type_;
  }

  CodeObject() {
    ids_ = std::make_shared<VecString>();
    vals_ = std::make_shared<VecSObject>();
    consts_ = std::make_shared<VecSObject>();
    opcode_ = std::make_shared<VecOp>();
    children_ = std::make_shared<VecSCodeObject>();
  }

  void setObject(const SObject &object) { object_ = object; }
  SObject getObject() { return object_; }

  void setParent(const SCodeObject &parent) { parent_ = parent; }
  SCodeObject getParent() const { return parent_; }

  int pushConst(const SObject &o);
  SObject getConst(int id) { return consts_->at(id); }

  int pushId(std::string var);
  int getId(std::string var, int &l);
  int getId(std::string var) {
    int l;
    int id = getId(var, l);
    if (l != 0)
      return -1;
    return id;
  }

  void setBlockType(BlockType type) { type_ = type; }
  BlockType getBlockType() const { return type_; }

  void storeIdValue(const SObject &value, int id, int level = 0);
  SObject getIdValue(int id, int level = 0);

  SVecOp getOpCode() { return opcode_; }
  void pushOp(Op op) { opcode_->push_back(op); }

  void addChild(const SCodeObject &c);
  SCodeObject getChild(int id) { return children_->at(id); }

  int getChildId(const SCodeObject &c);
};

#endif
