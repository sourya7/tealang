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
        assert(builder.get() != nullptr);
        if(t->tag == Tags::OP){
            auto op = GUARD_CAST<OPTok*>(t.get());
            builder->PerformOP(op->value);
        }
        else if(t->tag == Tags::BSQO){
            auto call = GUARD_CAST<CallAST*>(t->GetLeft().get());
            call->GenerateIR(builder);
        }
        else if(t->tag == Tags::ID) {
            auto wt = GUARD_CAST<WordTok*>(t.get());
            builder->LoadValue(wt->value);
        }
        else{
            auto o = Object::FromToken(t.get());
            builder->LoadConst(o);
        }
    }
}
