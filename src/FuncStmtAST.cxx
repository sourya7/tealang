#include "FuncStmtAST.h"
#include "WordTok.h"
#include "IRBuilder.h"
#include "SeqAST.h"

/*
 * defun bla:a andB:b
 *   var a = 2
 * endfun
 * PUSH_VAL b
 * PUSH_VAL a
 * call bla:andB:
 *
 * LOAD_VAL a
 * LOAD_VAL b
 * LOAD_CONST 2
 * STORE_VAL a
 * RETURN
 */
void FuncStmtAST::GenerateIR(IRBuilder* b){
    NodeAST* root= left;
    NodeAST* tmp = root; 
    string funName;

    IRBuilder* child = new IRBuilder(b);

    while(tmp->GetLeft() != nullptr){
        NodeAST* param = tmp->GetLeft();
        if(param->GetType() == NodeType::PARAM){
            //its a param, val pair
            funName += static_cast<WordTok*>(param->GetLeft())->value;
            child->DeclVar(static_cast<Token*>(param->GetRight()));
        }
        else{
            //its a simple id
            funName += static_cast<WordTok*>(param)->value;
            break;
        }
        tmp = tmp->GetRight();
    }

    right->GenerateIR(child);
    //map<string, int>
    //b->StoreFunction(funName, child);
    //[bla:2 andB:3]
    // push 3
    // push 2
    // call 1
}

