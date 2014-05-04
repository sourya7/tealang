#include "Debug.h"
#include "VM.h"
#include "Num.h"
#include "Frame.h"
#include "OPCode.h"
#include "CFunction.h"
#include "CodeObject.h"
#include "FunctionObj.h"

stack<Object*> VM::vmStack;
void VM::ExecCode(CodeObject* co){
    GCVecOP ops = co->GetOPS();
    auto op = ops.begin();
    while(op != ops.end()){  //auto it = ops.begin(); it != ops.end(); ++it){
    Object* i;
    Object* j;
    FunctionObj* fn;
    switch(op->opc){
        case OPC::ADD:
            DEBUG("OP::ADD");
            i = VM::Pop();
            j = VM::Pop();
            VM::Push(Num::Add(i, j));
            break;
        case OPC::SUB:
            DEBUG("OP::SUB");
            i = VM::Pop();
            j = VM::Pop();
            VM::Push(Num::Sub(i, j));
            break;
        case OPC::MULT:
            DEBUG("OP::MULT");
            i = VM::Pop();
            j = VM::Pop();
            VM::Push(Num::Mul(i, j));
            break;
        case OPC::LOAD_CONSTANT:
            DEBUG("OP::PUSH_CONSTANT");
            assert(op->HasArgA());
            i = co->GetConst(op->GetArgA());
            VM::Push(i);
            break;
        case OPC::LOAD_VALUE:
            DEBUG("OP::LOAD_VALUE");
            assert(op->HasArgA());
            assert(op->HasArgB());
            i = co->GetIDVal(op->GetArgA(), op->GetArgB());
            VM::Push(i);
            break;
        case OPC::STORE_VALUE:
            DEBUG("OP::STORE_VALUE");
            assert(op->HasArgA());
            assert(op->HasArgB());
            co->StoreIDVal(VM::Pop(), op->GetArgA(), op->GetArgB());
            break;
        case OPC::JMP_IF:
            DEBUG("OP::JMP_IF");
            assert(op->HasArgA());
            if(VM::Pop()->IsTrue()) VM::ExecCode(co->GetChild(op->GetArgA()));
            break;
        case OPC::JMP_IF_ELSE:
            DEBUG("OP::JMP_IF_ELSE");
            assert(op->HasArgA());
            //For if, we consume the else statment
            //For else, we consume the if statment
            if(VM::Pop()->IsTrue()) { VM::ExecCode(co->GetChild(op->GetArgA())); op++; }
            else { ++op; VM::ExecCode(co->GetChild(op->GetArgA())); }
            break;
        case OPC::CALL:{
            DEBUG("OP::CALL");
            assert(op->HasArgA());
            assert(op->HasArgB());
            fn = GUARD_CAST<FunctionObj*>(co->GetIDVal(op->GetArgA(), op->GetArgB()));
            if(fn->IsCFunction()){
                VM::ExecCode(fn->GetObjectCode());
                break;
            }
            //Letting it pass through intended
        }
        case OPC::C_CALL:{
            CFunction::Call(fn);
            break;
        }
        default:
            assert(false && "Not Implemented Yet!");
            break;
    }  ++op; //increment the op
    } //end switch, end for
}
