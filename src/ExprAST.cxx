#include "IRBuilder.h"
#include "ExprAST.h"
#include "WordTok.h"
#include "Debug.h"
#include "OPTok.h"
#include "Object.h"
using std::cerr;

void ExprAST::GenerateIR(IRBuilder* builder){
    for(auto t : expr){
        assert(builder != nullptr);
        if(t->tag == Tags::OP){
            OPTok* op = (OPTok*)t;
            builder->PerformOP(op->value);
        }
        else if(t->tag != Tags::ID) {
            Object* o = Object::FromToken(t);
            builder->LoadConst(o);
        }
        else{
            WordTok* wt = (WordTok*)t;
            builder->LoadValue(wt->value);
        }
    }
}
