
#include "Debug.h"
#include "IRBuilder.h"
#include "Token.h"
#include "WordTok.h"
#include "Object.h"
#include "OPTok.h"
#include "OPCode.h"
#include "CodeObject.h"


string arr[] = {
    "AND","BAND","OR","BOR","DECR","SUB","INCR","ADD","POWER","MULT","NEQ",
    "NOT","LEQ","LSHIFT","LT","GEQ","RSHIFT","GT","DIV","INV","XOR","EQ", "MOD",

    /* "Internal OP's */
    "LOAD_CONSTANT", "LOAD_VALUE"
};

IRBuilder* IRBuilder::builder = nullptr;
IRBuilder::IRBuilder() { co = new CodeObject();  }

/*
 *
 */
IRBuilder* IRBuilder::GetBuilder(){
    if(builder == nullptr) builder = new IRBuilder();
    return builder;
}

/*
 *  
 */
void IRBuilder::PerformOP(Token* t){
    assert(t->tag == Tags::OP);
    OPTok* op = (OPTok*)t;
    OPC opv = op->value;
    co->PushOP(OP(opv));
}

/*
 *
 */
void IRBuilder::PushValue(Token* t){
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

//
// Make sure that it is a word
//
WordTok* GUARD_WORD(Token* t){
    WordTok* wt = dynamic_cast<WordTok*>(t);
    assert(wt != nullptr);
    return wt;
}

//
//
//
void IRBuilder::StoreValue(Token* t){
    WordTok* wt = GUARD_WORD(t);
    int id = co->GetID(wt->value);
    assert(id != -1 && "Variable not declared");
    co->PushOP(OP(OPC::STORE_VALUE, id));
}

void IRBuilder::DeclVar(Token* t){
    WordTok* wt = GUARD_WORD(t);
    //Is it already declared? 
    assert(co->GetID(wt->value) == -1 && "Variable already declared!");
    co->PushID(wt->value);
}

/*
 *
 */
CodeObject* IRBuilder::GetCodeObject(){
    return co;
}

