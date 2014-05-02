#include <string>
#include <cassert>
#include <iostream>
#include "NodeAST.h"
#include "IRBuilder.h"
#include "Debug.h"

using std::string;
using std::cerr;

void NodeAST::GenerateIR(IRBuilder* builder) {
    switch(type){
        case NodeType::VAR:
            //declare the variable;
            builder->DeclVar((Token*)left);
            //if the right exists, call it
            if(right != nullptr) right->GenerateIR(builder);
            break;
        case NodeType::ASSIGN:
            //eval the right node
            right->GenerateIR(builder);
            //store the val
            builder->StoreValue((Token*)left);
            break;
        default:
            assert(false && "This should not be called!");
    }
}

