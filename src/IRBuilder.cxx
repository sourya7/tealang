#include "Debug.h"
#include "IRBuilder.h"
#include "Object.h"
#include "OPCode.h"
#include "CodeObject.h"
#include "FunctionObj.h"


IRBuilder::IRBuilder() { co = make_shared<CodeObject>(); }
IRBuilder::IRBuilder(SIRBuilder b) {
    auto parent = b->GetCodeObject();
    co = make_shared<CodeObject>(parent);
    parent->AddChild(co);
}

void IRBuilder::CondJump(SIRBuilder ifBlk){
    int childId = co->GetChildID(ifBlk->GetCodeObject());
    assert(childId != -1);
    co->PushOP(OP(OPC::JMP_IF, childId));
}

void IRBuilder::CondJump(SIRBuilder ifBlk, SIRBuilder elBlk){
    int ifId = co->GetChildID(ifBlk->GetCodeObject());
    int elId = co->GetChildID(elBlk->GetCodeObject());
    co->PushOP(OP(OPC::JMP_IF_ELSE, ifId));
    co->PushOP(OP(OPC::JMP_IF_ELSE, elId));
}

void IRBuilder::PerformOP(OPC op){
    co->PushOP(OP(op));
}

// 2+4
// LOAD_CONST 1 (2)
// LOAD_CONST 2 (4)
// BINARY_ADD 
void IRBuilder::LoadConst(SObject c){
    int id = co->PushConst(c);
    co->PushOP(OP(OPC::LOAD_CONSTANT, id));
}

// 2 + a
// LOAD_CONST 1 (2)
// LOAD_CONST 1 (a)
// BINARY_ADD
void IRBuilder::LoadValue(string v){
    int l;
    int id = co->GetID(v,l);
    assert(id != -1);
    co->PushOP(OP(OPC::LOAD_VALUE,id,l));
}

// BINARY_ADD     (Operation pushes the value to the stack)
// STORE_VALUE 0  (Store the value from the stack into a variable)
void IRBuilder::StoreValue(string v){
    int l = 0;
    int id = co->GetID(v,l);
    assert(id != -1 && "Variable not declared");
    co->PushOP(OP(OPC::STORE_VALUE,id,l));
}

void IRBuilder::DeclVar(string v){
    assert(co->GetID(v) == -1 && "Variable already declared!");
    co->PushID(v);
}

void IRBuilder::DeclVar(string v, SObject o){
    assert(co->GetID(v) == -1 && "Variable already declared!");
    int id = co->PushID(v);
    co->StoreIDVal(o,id);
}

void IRBuilder::DeclFunc(string n, int ac, SIRBuilder b){
    b->GetCodeObject()->SetType(CT::FUNCTION);
    auto fo = make_shared<FunctionObj>(n, ac, b->GetCodeObject());
    int id = co->GetID(n);
    assert(id != -1);
    co->StoreIDVal(fo,id);
}

void IRBuilder::DeclCFunc(string n, int ac){
    auto fo = make_shared<FunctionObj>(n, ac); 
    DeclVar(n, fo);
}

SCodeObj IRBuilder::GetCodeObject(){
    return co;
}

void IRBuilder::Return(bool hasArg){
    co->PushOP(OP(OPC::RETURN, hasArg));
}

void IRBuilder::DeclWhile(SIRBuilder expr, SIRBuilder body){
    int exprID = co->GetChildID(expr->GetCodeObject());
    int bodyID = co->GetChildID(body->GetCodeObject());
    assert(exprID != -1);
    assert(bodyID != -1);
    co->PushOP(OP(OPC::WHILE, exprID, bodyID));
}

void IRBuilder::CallFunc(string fn){
    int l;
    int id = co->GetID(fn,l);
    assert(id != -1);
    co->PushOP(OP(OPC::CALL,id,l));
}
