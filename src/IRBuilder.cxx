
#include "Debug.h"
#include "IRBuilder.h"
#include "Token.h"
#include "WordTok.h"
#include "Object.h"
#include "OPTok.h"
#include "OPCode.h"
#include "CodeObject.h"


IRBuilder::IRBuilder() { co = new CodeObject(); }
IRBuilder::IRBuilder(IRBuilder* b) {
    CodeObject* parent = b->GetCodeObject();
    co = new CodeObject(parent);
    parent->AddChild(co);
}

void IRBuilder::CondJump(IRBuilder* ifBlk){
    int childId = co->GetChildID(ifBlk->GetCodeObject());
    assert(childId != -1);
    co->PushOP(OP(OPC::JMP_IF, childId));
}

void IRBuilder::CondJump(IRBuilder* ifBlk, IRBuilder* elBlk){
    int ifId = co->GetChildID(ifBlk->GetCodeObject());
    int elId = co->GetChildID(elBlk->GetCodeObject());
    co->PushOP(OP(OPC::JMP_IF_ELSE, ifId));
    co->PushOP(OP(OPC::JMP_IF_ELSE, elId));
}

void IRBuilder::PerformOP(Token* t){
    assert(t->tag == Tags::OP);
    OPTok* op = (OPTok*)t;
    OPC opv = op->value;
    co->PushOP(OP(opv));
}

void IRBuilder::LoadValue(Token* t){
    //check if t is a variable vs a constant
    if(t->tag != Tags::ID){
        Object* o = Object::FromToken(t);
        int id = co->PushConst(o);   
        co->PushOP(OP(OPC::LOAD_CONSTANT, id));
    }
    else{
        WordTok* wt = (WordTok*)t;
        int id = co->GetID(((WordTok*)t)->value);
        assert(id != -1);
        co->PushOP(OP(OPC::LOAD_VALUE, id)); 
    }
}

WordTok* GUARD_WORD(Token* t){
    WordTok* wt = dynamic_cast<WordTok*>(t);
    assert(wt != nullptr);
    return wt;
}

void IRBuilder::StoreValue(Token* t){
    WordTok* wt = GUARD_WORD(t);
    int id = co->GetID(wt->value);
    assert(id != -1 && "Variable not declared");
    co->PushOP(OP(OPC::STORE_VALUE, id));
}

void IRBuilder::DeclVar(Token* t){
    WordTok* wt = GUARD_WORD(t);
    assert(co->GetID(wt->value) == -1 && "Variable already declared!");
    co->PushID(wt->value);
}

CodeObject* IRBuilder::GetCodeObject(){
    return co;
}

