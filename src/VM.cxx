#include <cassert>
#include <iostream>
#include "Debug.h"
#include "VM.h"
#include "Frame.h"
#include "OPCode.h"
#include "CodeObject.h"
using std::cerr;

void VM::ExecCode(CodeObject* co){
    VM* vm = new VM();
    vector<OP> ops = co->GetOPS();
    for(OP op : ops){
    switch(op){
        case OP::ADD:
            DEBUG("OP::ADD");
            //get the top
            //get the top
            //add them up
            break;
        case OP::SUB:
            DEBUG("OP::SUB");
            //get the top
            //get the top
            //add them up
            break;
        case OP::MULT:
            DEBUG("OP::MULT");
            //get the top
            //get the top
            //add them up
            break;
        case OP::LOAD_CONSTANT:
            DEBUG("OP::LOAD_CONSTANT");
            break;
        case OP::LOAD_VALUE:
            DEBUG("OP::LOAD_VALUE");
            break;
        default:
            assert(false && "Not Implemented Yet!");
    }} //end switch, end for
}
