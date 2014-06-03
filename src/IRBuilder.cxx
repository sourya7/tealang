#include <cstring>
#include "Debug.h"
#include "IRBuilder.h"
#include "StringObj.h"
#include "Object.h"
#include "OPCode.h"
#include "CodeObject.h"
#include "FunctionObj.h"
#include "ClassObj.h"

SIRBuilder IRBuilder::_global = MakeShared<IRBuilder>();
IRBuilder::IRBuilder() { co = MakeShared<CodeObject>(); }
IRBuilder::IRBuilder(SIRBuilder b) {
  auto parent = b->GetCodeObject();
  co = MakeShared<CodeObject>(parent);
  parent->AddChild(co);
}

SIRBuilder IRBuilder::GetGlobal(){
  return _global;
}

void IRBuilder::CondJump(SIRBuilder ifBlk) {
  int childId = co->GetChildID(ifBlk->GetCodeObject());
  assert(childId != -1);
  co->PushOP(OP(OPC::JMP_IF_ELSE, childId));
}

void IRBuilder::CondJump(SIRBuilder ifBlk, SIRBuilder elBlk) {
  int ifId = co->GetChildID(ifBlk->GetCodeObject());
  int elId = co->GetChildID(elBlk->GetCodeObject());
  co->PushOP(OP(OPC::JMP_IF_ELSE, ifId, elId));
}

void IRBuilder::PerformOP(OPC op) { co->PushOP(OP(op)); }

void IRBuilder::LoadConst(SObject c) {
  int id = co->PushConst(c);
  co->PushOP(OP(OPC::LOAD_CONSTANT, id));
}

void IRBuilder::LoadValue(string v) {
  int l;
  int id = co->GetID(v, l);
  assert(id != -1);
  co->PushOP(OP(OPC::LOAD_VALUE, id, l));
}

void IRBuilder::StoreValue(string v) {
  int l = 0;
  int id = co->GetID(v, l);
  assert(id != -1 && "Variable not declared");
  co->PushOP(OP(OPC::STORE_VALUE, id, l));
}

void IRBuilder::DeclVar(string v) {
  assert(co->GetID(v) == -1 && "Variable already declared!");
  co->PushID(v);
}

void IRBuilder::DeclVar(string v, SObject o) {
  assert(co->GetID(v) == -1 && "Variable already declared!");
  int id = co->PushID(v);
  co->StoreIDVal(o, id);
}

void IRBuilder::DeclFunc(bool i, string n, int ac, SIRBuilder b) {
  auto fun_co = b->GetCodeObject();
  // TODO: Is this a hack? A better way to initialize?
  if (i)
    fun_co->PushOP(OP(OPC::INIT_INSTANCE));

  auto fo = MakeShared<FunctionObj>(n, ac, fun_co,i);
  int id = co->GetID(n);
  assert(id != -1);
  co->StoreIDVal(fo, id);
  // load the into the stack
}

SCodeObj IRBuilder::GetCodeObject() { return co; }

void IRBuilder::Return(bool hasArg) { co->PushOP(OP(OPC::RETURN, hasArg)); }

void IRBuilder::DeclWhile(SIRBuilder expr, SIRBuilder body) {
  int exprID = co->GetChildID(expr->GetCodeObject());
  int bodyID = co->GetChildID(body->GetCodeObject());
  assert(exprID != -1);
  assert(bodyID != -1);
  co->PushOP(OP(OPC::WHILE, exprID, bodyID));
}

void IRBuilder::CallFunc(string fn) {
  int l;
  int id = co->GetID(fn, l);
  assert(id != -1);
  co->PushOP(OP(OPC::CALL, id, l));
}

void IRBuilder::DeclClass(string n, SIRBuilder b) {
  // Todo, add a default init if there is none
  auto b_co = b->GetCodeObject();
  auto cls_o = MakeShared<ClassObj>(n, b_co);
  int id = co->GetID(n);
  assert(id != -1);
  co->StoreIDVal(cls_o, id);
}

void IRBuilder::CallMethod(string method) {
  // StringObj takes ownership of this
  // TODO turn this into unique_ptr
  SObject strObj = MakeShared<StringObj>(method);
  LoadConst(strObj);
  co->PushOP(OP(OPC::CALL_METHOD));
}
