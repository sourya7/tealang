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
  // values
  std::map<std::string,SObject> valmap_;
  // constants in the codeobject scope
  SVecSObject consts_;
  // opcodes for this codeobject
  SVecOp opcode_;
  SVecSCodeObject children_;
  SCodeObject parent_ = nullptr;
  SObject object_ = nullptr;
  BlockType type_ = BlockType::EXPR;
  static std::map<std::string, SObject>::iterator findVar(CodeObject *code,
                                                          std::string var);

public:
  CodeObject(SCodeObject parent) : CodeObject() { parent_ = parent; }

  CodeObject(const CodeObject &rhs) {
    parent_ = rhs.parent_;
    children_ = rhs.children_;
    opcode_ = rhs.opcode_;
    consts_ = rhs.consts_;
    object_ = rhs.object_;
    type_ = rhs.type_;
    valmap_ = rhs.valmap_;
  }

  CodeObject() {
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



  void setBlockType(BlockType type) { type_ = type; }
  BlockType getBlockType() const { return type_; }

  void addVar(std::string name);
  void storeValue(std::string name, const SObject &value);
  SObject getValue(std::string name);

  SVecOp getOpCode() { return opcode_; }
  void pushOp(Op op) { opcode_->push_back(op); }

  void addChild(const SCodeObject &c);
  SCodeObject getChild(int id) { return children_->at(id); }

  int getChildId(const SCodeObject &c);
};

#endif
