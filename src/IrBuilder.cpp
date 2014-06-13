#include <cstring>
#include "Debug.h"
#include "IrBuilder.h"
#include "Objects/StringObject.h"
#include "Object.h"
#include "OpCode.h"
#include "CodeObject.h"
#include "Objects/FunctionObject.h"
#include "Objects/ClassObject.h"

IrBuilder::IrBuilder() { codeObject_ = std::make_shared<CodeObject>(); }
IrBuilder::IrBuilder(SIrBuilder b) {
  auto parent = b->getCodeObject();
  codeObject_ = std::make_shared<CodeObject>(parent);
  parent->addChild(codeObject_);
}

void IrBuilder::condJump(SIrBuilder ifBlk) {
  auto ifCo = ifBlk->getCodeObject();
  ifCo->setBlockType(BlockType::IF);
  int childId = codeObject_->getChildId(ifCo);
  assert(childId != -1);
  codeObject_->pushOp(Op(Opc::JMP_IF_ELSE, childId));
}

void IrBuilder::condJump(SIrBuilder ifBlk, SIrBuilder elBlk) {
  auto ifCo = ifBlk->getCodeObject();
  ifCo->setBlockType(BlockType::IF);
  auto elCo = elBlk->getCodeObject();
  elCo->setBlockType(BlockType::IF);
  int ifId = codeObject_->getChildId(ifCo);
  int elId = codeObject_->getChildId(elCo);
  assert(ifId != -1 && elId != -1);
  codeObject_->pushOp(Op(Opc::JMP_IF_ELSE, ifId, elId));
}

void IrBuilder::performOp(Opc op) { codeObject_->pushOp(Op(op)); }

void IrBuilder::loadConst(SObject c) {
  int id = codeObject_->pushConst(c);
  codeObject_->pushOp(Op(Opc::LOAD_CONSTANT, id));
}

void IrBuilder::loadValue(std::string v) {
  int l;
  int id = codeObject_->getId(v, l);
  assert(id != -1);
  codeObject_->pushOp(Op(Opc::LOAD_VALUE, id, l));
}

void IrBuilder::storeValue(std::string v) {
  int l = 0;
  int id = codeObject_->getId(v, l);
  assert(id != -1 && "Variable not declared");
  codeObject_->pushOp(Op(Opc::STORE_VALUE, id, l));
}

void IrBuilder::declVar(std::string v) {
  assert(codeObject_->getId(v) == -1 && "Variable already declared!");
  codeObject_->pushId(v);
}

void IrBuilder::declVar(std::string v, SObject o) {
  assert(codeObject_->getId(v) == -1 && "Variable already declared!");
  int id = codeObject_->pushId(v);
  codeObject_->storeIdValue(o, id);
}

void IrBuilder::declFunc(bool i, std::string n, int ac, SIrBuilder b) {
  auto fun_co = b->getCodeObject();
  // TODO: Is this a hack? A better way to initialize?
  if (i)
    fun_co->pushOp(Op(Opc::INIT_INSTANCE));

  auto fo = std::make_shared<FunctionObject>(n, ac, fun_co, i);
  int id = codeObject_->getId(n);
  assert(id != -1);
  codeObject_->storeIdValue(fo, id);
  // load the into the stack
}

SCodeObject IrBuilder::getCodeObject() { return codeObject_; }

void IrBuilder::returnValue(bool hasArg) {
  codeObject_->pushOp(Op(Opc::RETURN, hasArg));
}

void IrBuilder::declWhile(SIrBuilder whileBlk) {
  auto whileCo = whileBlk->getCodeObject();
  whileCo->setBlockType(BlockType::WHILE);

  int whileCid = codeObject_->getChildId(whileCo);
  assert(whileCid != -1);
  codeObject_->pushOp(Op(Opc::WHILE, whileCid));
}

void IrBuilder::breakFlow() { codeObject_->pushOp(Op(Opc::BREAK)); }

void IrBuilder::callFunc(std::string fn) {
  int l;
  int id = codeObject_->getId(fn, l);
  assert(id != -1);
  codeObject_->pushOp(Op(Opc::CALL, id, l));
}

void IrBuilder::declClass(std::string n, SIrBuilder b) {
  // Todo, add a default init if there is none
  auto b_co = b->getCodeObject();
  auto cls_o = std::make_shared<ClassObject>(n, b_co);
  int id = codeObject_->getId(n);
  assert(id != -1);
  codeObject_->storeIdValue(cls_o, id);
}

void IrBuilder::callMethod(std::string method) {
  // StringObj takes ownership of this
  // TODO turn this into unique_ptr
  SObject strObj = std::make_shared<StringObject>(method);
  loadConst(strObj);
  codeObject_->pushOp(Op(Opc::CALL_METHOD));
}
