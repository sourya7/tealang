#include <string>
#include <cassert>
#include <iostream>
#include "NodeAST.h"
#include "IRBuilder.h"
#include "Debug.h"

using std::string;
using std::cerr;

void NodeAST::Display(int level) {
    cerr << string(level*2, ' ');
    switch(type){
        case NodeType::NODE: cerr << "NODE"; break;
        case NodeType::SEQ: cerr << "SEQ"; break;
        case NodeType::CALL: cerr << "CALL"; break;
        case NodeType::PARAM: cerr << "PARAM"; break;
        case NodeType::IFSTMT: cerr << "IFSTMT"; break;
        case NodeType::FSTMT: cerr << "FSTMT"; break;
        case NodeType::ASSIGN: cerr << "ASSIGN"; break;
        case NodeType::EXPR: cerr << "EXPR"; break;
        case NodeType::TOKEN: cerr << "TOKEN"; break;
    }
    cerr << "\n";
    if(left != nullptr) left->Display(level+1);
    if(right != nullptr) right->Display(level+1);
}

void NodeAST::GenerateIR() {
    switch(type){
        case NodeType::ASSIGN:
            DEBUG("GenerateIR()::ASSIGN");
            //eval the right node
            right->GenerateIR();
            //store the val
            //builder->StoreValue((*)left);
            break;
        default:
            assert(false && "This should not be called!");
    }
}

