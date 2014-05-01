#include <cassert>
#include "VM.h"
#include "Frame.h"
#include "OPCode.h"
#include "CodeObject.h"

void VM::ExecCode(CodeObject* co){
    vector<OP> ops = co->GetOPS();

    for(OP op : ops){
    switch(op){
        case OP::ADD:
            //get the top
            //get the top
            //add them up
            break;
        case OP::SUB:
            //get the top
            //get the top
            //add them up
            break;
        default:
            assert(false && "Not Implemented Yet!");
    }} //end switch, end for
}
