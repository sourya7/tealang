#include "IfStmtAST.h"
#include "Debug.h"
#include "IRBuilder.h"

void IfStmtAST::GenerateIR(IRBuilder* builder) {
    IRBuilder* ifBlkBuild = new IRBuilder(builder);
    
    left->GenerateIR(builder); //build the expression
    right->GenerateIR(ifBlkBuild); //build the ifblock

    //If the last expressoin evals to true, jump to the child
    if(elseBlk == nullptr) builder->CondJump(ifBlkBuild); 
    else {
        IRBuilder* elBlkBuild = new IRBuilder(builder);
        elseBlk->GenerateIR(elBlkBuild);
        builder->CondJump(ifBlkBuild, elBlkBuild);
    }
}

