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
            //load the val into the var
            builder->StoreValue((Token*)left);
            break;
        case NodeType::CALL: 
            assert(false && "CALL");
        case NodeType::PARAM: 
            assert(false && "PARAM");
        case NodeType::IFSTMT:
            assert(false && "IFSTMT");
        case NodeType::FSTMT:
            assert(false && "FSTMT");
        case NodeType::EXPR: 
            assert(false && "EXPR");
        case NodeType::TOKEN: 
            assert(false && "TOKEN");
        default:
            assert(false && "This should not be called!");
    }
}

