#include <string>
#include <iostream>
#include "NodeAST.h"
#include "WordTok.h"
#include "IRBuilder.h"
#include "Debug.h"
#include "Object.h"

using std::string;
using std::cerr;

void NodeAST::GenerateIR(SIRBuilder builder){
    switch(type){
        case NodeType::VAR:
            //declare the variable;
            builder->DeclVar(GUARD_CAST<WordTok*>(POINTER_VAL(left))->value);
            //if the right exists, call it
            if(POINTER_VAL(right) != nullptr) right->GenerateIR(builder);
            break;
        case NodeType::ASSIGN:
            //eval the right node
            right->GenerateIR(builder);
            //load the val into the var
            builder->StoreValue(GUARD_CAST<WordTok*>(POINTER_VAL(left))->value);
            break;
        case NodeType::TOKEN: 
        {
            //TODO, this is a hack
            auto t = GUARD_CAST<Token*>(this);
            if(t->tag == Tags::ID){
                auto wt = GUARD_CAST<WordTok*>(t);
                builder->LoadValue(wt->value);
            }
            else { builder->LoadConst(Object::FromToken(t)); }
            break;
        }
        case NodeType::RETURN: 
        {
            if(POINTER_VAL(left) == nullptr) builder->Return();
            else{
                left->GenerateIR(builder);
                builder->ReturnArg();
                break;
            }
        }

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
        default:
        assert(false && "This should not be called!");
    }
}

