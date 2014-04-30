
#include "Debug.h"
#include "IRBuilder.h"
#include "Token.h"
#include "TObject.h"
#include "OPTok.h"
#include "OPCode.h"

IRBuilder* IRBuilder::builder = nullptr;
IRBuilder* IRBuilder::GetBuilder(){
    if(builder == nullptr) builder = new IRBuilder();
    return builder;
}

uint IRBuilder::GetOPSize(Token* t){
    return 0;
}

/*
 * 
 */
void IRBuilder::PerformOP(Token* t){
    assert(t->tag == Tags::OP);
    OPTok* op = (OPTok*)t;
    DEBUG("IRBuilder::PerformOP()");
}


/*
 *
 */
void IRBuilder::PushValue(Token* t){
    TObject* o = TObject::FromToken(t);
    //check if t is a variable vs a constant
    //codeObj->PushValue(o);
    DEBUG("IRBuilder::PushParams()");
}

/*
 *
 */
void IRBuilder::StoreValue(Token* t){
    //Pop value from the stack
    //Store t in a map with the assiciated value
    DEBUG("IRBuilder::StoreValue()");
}

