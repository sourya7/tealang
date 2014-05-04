#include "Debug.h"
#include "VM.h"
#include "Num.h"
#include "Frame.h"
#include "OPCode.h"
#include "CodeObject.h"
#include "FunctionObj.h"

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
            DEBUG("OP::PUSH_CONSTANT");
            assert(op->HasArgA());
            i = co->GetConst(op->GetArgA());
            vm->Push(i);
            break;
        case OPC::LOAD_VALUE:
            DEBUG("OP::LOAD_VALUE");
            assert(op->HasArgA());
            assert(op->HasArgB());
            i = co->GetIDVal(op->GetArgA(), op->GetArgB());
            vm->Push(i);
            break;
        case OPC::STORE_VALUE:
            DEBUG("OP::STORE_VALUE");
            assert(op->HasArgA());
            assert(op->HasArgB());
            co->StoreIDVal(vm->Pop(), op->GetArgA(), op->GetArgB());
            break;
        case OPC::JMP_IF:
            DEBUG("OP::JMP_IF");
            assert(op->HasArgA());
            if(vm->Pop()->IsTrue()) VM::ExecCode(co->GetChild(op->GetArgA()));
            break;
        case OPC::JMP_IF_ELSE:
            DEBUG("OP::JMP_IF_ELSE");
            assert(op->HasArgA());
            //For if, we consume the else statment
            //For else, we consume the if statment
            if(vm->Pop()->IsTrue()) { VM::ExecCode(co->GetChild(op->GetArgA())); op++; }
            else { ++op; VM::ExecCode(co->GetChild(op->GetArgA())); }
            break;
        case OPC::CALL:{
            DEBUG("OP::CALL");
            assert(op->HasArgA());
            assert(op->HasArgB());
            auto fn = GUARD_CAST<FunctionObj*>(co->GetIDVal(op->GetArgA(), op->GetArgB()));
            VM::ExecCode(fn->GetObjectCode());
            break;
        }
        default:
            assert(false && "Not Implemented Yet!");
            break;
    }  ++op; //increment the op
    } //end switch, end for
}
