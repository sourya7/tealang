
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
void IRBuilder::DumpCodeObject(){
    const vector<OP> ops = co->GetOPS();
    cerr << "\n";
    for(OP o : ops){
        int v = static_cast<int>(o);
        cerr << "OP " << arr[v - 200] << "\n";
    }
}

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
    OP opv = op->value;
    co->PushOP(op->value);
    DEBUG("IRBuilder::PerformOP()");
}

/*
 *
 */
void IRBuilder::PushValue(Token* t){
    //check if t is a variable vs a constant
    if(t->tag != Tags::ID){
        Object* o = Object::FromToken(t);
        int id = co->PushConst(o);   
        co->PushOP(OP::LOAD_CONSTANT, id);
    }
    else{
        WordTok* wt = (WordTok*)t;
        int id = co->PushID(((WordTok*)t)->value);
        co->PushOP(OP::LOAD_VALUE, id); 
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

