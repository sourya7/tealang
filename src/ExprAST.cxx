#include <vector>
#include <iostream>
#include "IRBuilder.h"
#include "ExprAST.h"
#include "WordTok.h"
#include "Debug.h"

using std::vector;
using std::cerr;

void ExprAST::GenerateIR(){
    DEBUG("ExprAST::GenerateIR()");
    IRBuilder* builder = IRBuilder::GetBuilder();
    for(auto t : expr){
        assert(builder != nullptr);
        if(t->tag == Tags::OP) builder->PerformOP(t);
        else builder->PushValue(t);
    }
}
