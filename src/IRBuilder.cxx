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
void IRBuilder::PushParams(Token* t){
    DEBUG("IRBuilder::PushParams()");
}

/*
 *
 */
void IRBuilder::StoreValue(Token* t){
    DEBUG("IRBuilder::StoreValue()");
}

