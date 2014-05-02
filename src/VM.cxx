#include "Debug.h"
#include "VM.h"
#include "Num.h"
#include "Frame.h"
#include "OPCode.h"
#include "CodeObject.h"

void VM::ExecCode(CodeObject* co){
    VM* vm = new VM();
    vector<OP> ops = co->GetOPS();
    for(OP op : ops){
    Object* i;
    Object* j;
    switch(op.opc){
        case OPC::ADD:
            DEBUG("OP::ADD");
            i = vm->Pop();
            j = vm->Pop();
            vm->Push(Num::Add(i, j));
            break;
        case OPC::SUB:
            DEBUG("OP::SUB");
            i = vm->Pop();
            j = vm->Pop();
            vm->Push(Num::Sub(i, j));
            break;
        case OPC::MULT:
            DEBUG("OP::MULT");
            i = vm->Pop();
            j = vm->Pop();
            vm->Push(Num::Mul(i, j));
            break;
        case OPC::LOAD_CONSTANT:
            DEBUG("OP::LOAD_CONSTANT");
            assert(op.HasArg());
            i = co->GetConst(op.GetArg());
            vm->Push(i);
            break;
        case OPC::LOAD_VALUE:
            DEBUG("OP::LOAD_VALUE");
            assert(op.HasArg());
            i = co->GetIDVal(op.GetArg());
            vm->Push(i);
            break;
        case OPC::STORE_VALUE:
            DEBUG("OP::STORE_VALUE");
            assert(op.HasArg());
            co->StoreIDVal(op.GetArg(), vm->Pop());
            break;
        default:
            assert(false && "Not Implemented Yet!");
    }} //end switch, end for
}
