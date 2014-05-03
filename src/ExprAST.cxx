#include <iostream>
#include "IRBuilder.h"
#include "ExprAST.h"
#include "WordTok.h"
#include "Debug.h"

using std::cerr;

void ExprAST::GenerateIR(IRBuilder* builder){
    for(auto t : expr){
        assert(builder != nullptr);
        if(t->tag == Tags::OP) builder->PerformOP(t);
        else builder->LoadValue(t);
    }
}
