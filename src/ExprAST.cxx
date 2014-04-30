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
    for(auto t : expr){
        if(t->tag == Tags::OP) builder->PerformOP(t);
        else builder->PushValue(t);
    }
}
