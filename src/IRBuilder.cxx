
#include "Debug.h"
#include "IRBuilder.h"
#include "Token.h"
#include "Object.h"
#include "OPTok.h"
#include "OPCode.h"
#include "CodeObject.h"


IRBuilder* IRBuilder::builder = nullptr;
IRBuilder::IRBuilder() { cobj = new CodeObject();  }

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
    codeObj->PushOP(op->value);
    DEBUG("IRBuilder::PerformOP()");
}

/*
 *
 */
void IRBuilder::PushValue(Token* t){
    //check if t is a variable vs a constant
    if(t->tag != Tags::ID){
        Object* o = Object::FromToken(t);
        int id = codeObj->PushValue(o);   
        codeObj->PushOP(OP::LOAD_CONSTANT, id);
    }
    else{
        int id = codeObj->PushID((WordTok*)t->value);
        codeObj->PushOP(OP::LOAD_VALUE, 
    }
    DEBUG("IRBuilder::PushValue()");
}

/*
 *
 */
void IRBuilder::StoreValue(Token* t){
    //Pop value from the stack
    //Store t in a map with the assiciated value
    DEBUG("IRBuilder::StoreValue()");
}

