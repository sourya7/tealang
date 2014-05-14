#include "IRBuilder.h"
#include "ExprAST.h"
#include "WordTok.h"
#include "Debug.h"
#include "OPTok.h"
#include "CallAST.h"
#include "Object.h"
using std::cerr;


void ExprAST::GenerateIR(SIRBuilder builder){
    for(auto t : expr){
        if(t->tag == Tags::OP){
            auto op = GUARD_CAST<OPTok*>(POINTER_VAL(t));
            builder->PerformOP(op->value);
        }
        else if(t->tag == Tags::BSQO){
            auto call = GUARD_CAST<CallAST*>(POINTER_VAL(t->GetLeft()));
            call->GenerateIR(builder);
        }
        else if(t->tag == Tags::ID) {
            auto wt = GUARD_CAST<WordTok*>(POINTER_VAL(t));
            builder->LoadValue(wt->value);
        }
        else{
            auto o = Object::FromToken(POINTER_VAL(t));
            builder->LoadConst(o);
        }
    }
}
