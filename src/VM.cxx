#include "Debug.h"
#include "VM.h"
#include "Num.h"
#include "Frame.h"
#include "OPCode.h"
#include "CodeObject.h"

void VM::ExecCode(CodeObject* co){
    VM* vm = new VM();
    GCVecOP ops = co->GetOPS();
    auto op = ops.begin();
    while(op != ops.end()){  //auto it = ops.begin(); it != ops.end(); ++it){
    Object* i;
    Object* j;
    switch(op->opc){
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
            assert(op->HasArg());
            i = co->GetConst(op->GetArg());
            vm->Push(i);
            break;
        case OPC::LOAD_VALUE:
            DEBUG("OP::LOAD_VALUE");
            assert(op->HasArg());
            i = co->GetIDVal(op->GetArg());
            vm->Push(i);
            break;
        case OPC::STORE_VALUE:
            DEBUG("OP::STORE_VALUE");
            assert(op->HasArg());
            co->StoreIDVal(op->GetArg(), vm->Pop());
            break;
        case OPC::JMP_IF:
            DEBUG("OP::JMP_IF");
            assert(op->HasArg());
            if(vm->Pop()->IsTrue()) VM::ExecCode(co->GetChild(op->GetArg()));
            break;
        case OPC::JMP_IF_ELSE:
            DEBUG("OP::JMP_IF_ELSE");
            assert(op->HasArg());
            //For if, we consume the else statment
            //For else, we consume the if statment
            if(vm->Pop()->IsTrue()) { VM::ExecCode(co->GetChild(op->GetArg())); op++; }
            else { ++op; VM::ExecCode(co->GetChild(op->GetArg())); }
            break;
        default:
            assert(false && "Not Implemented Yet!");
            break;
    }  ++op; //increment the op
    } //end switch, end for
}
