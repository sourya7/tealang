
#include "Debug.h"
#include "IRBuilder.h"

IRBuilder* IRBuilder::builder;
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
    DEBUG("IRBuilder::PerformOP()");
}


/*
 *
 */
void IRBuilder::PushValue(Token* t){
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

