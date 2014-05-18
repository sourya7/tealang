#include "CallAST.h"
#include "ParamAST.h"
#include "IRBuilder.h"
#include "WordTok.h"

/*
 * Number of ways a function can be called
 * 1. [callA:2 andB:4]
 *    Here we are calling the function callA:andB:
 *    with the arguments [2,4]. The steps of generation
 *    are:
 *    a. Push 4 as a constant
 *    b. Push 2 as a constant
 *    c. Call "callA:andB:4"
 *
 *  2. [callA:a andB:b]
 *     We are calling the function with the variables [a,b]n
 *     We:
 *     a. Load the value of the constant b
 *     b. Load the value of the constant c
 *     c. Call "callA:andB:
 *
 *  3. [callA:(2+2) andB:b]
 *     Here, we have an expression to parse.
 *     a. Load the constant b
 *     b. Parse the expression and load its value
 *     c. Call "callA:andB:"
 *
 */
void CallAST::GenerateIR(SIRBuilder builder){
    auto paramAST = GUARD_CAST<ParamAST*>(POINTER_VAL(right));
    VecSNodeAST params = paramAST->GetParams();
    for(auto it=params.rbegin(), end=params.rend(); it != end; ++it){
        (*it)->GenerateIR(builder);
    }

    if(POINTER_VAL(left) != nullptr){
        //there is an object. 
        if(left->GetType() == NodeType::PARAM){
            //there is a function to generate an object
            assert(false);
            left->GenerateIR(builder);
        }
        else {
            //its simply an id to an object
            string val = GUARD_CAST<WordTok*>(POINTER_VAL(left))->value;
            builder->LoadValue(val);
        }
        builder->CallMethod(paramAST->GetName());
    }
    else {
        //its a simple function call
        builder->CallFunc(paramAST->GetName());
    }
    
}
