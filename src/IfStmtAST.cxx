#include "IfStmtAST.h"
#include "Debug.h"
#include "IRBuilder.h"

void IfStmtAST::GenerateIR(SIRBuilder builder) {
    auto ifBlkBuild = make_shared<IRBuilder>(builder);
    
    left->GenerateIR(builder); //build the expression
    right->GenerateIR(ifBlkBuild); //build the ifblock

    //If the last expressoin evals to true, jump to the child
    if(elseBlk.get() == nullptr) builder->CondJump(ifBlkBuild); 
    else {
        auto elBlkBuild = make_shared<IRBuilder>(builder);
        elseBlk->GenerateIR(elBlkBuild);
        builder->CondJump(ifBlkBuild, elBlkBuild);
    }
}

