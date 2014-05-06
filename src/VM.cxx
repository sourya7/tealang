#include "Debug.h"
#include "VM.h"
#include "ObjOP.h"
#include "Frame.h"
#include "OPCode.h"
#include "CFunction.h"
#include "CodeObject.h"
#include "FunctionObj.h"

GCStackObjPtr VM::vmStack;
bool VM::RetFlag = false;
void VM::ExecCode(CodeObject* co){
    VM::ResetFlags();
    GCVecOP ops = co->GetOPS();
    auto op = ops.begin();
    while(op != ops.end()){
    Object* i;
    Object* j;
    FunctionObj* fn;
    if(VM::RetFlag) { VM::ResetFlags();  return; }
    switch(op->opc){
        case OPC::ADD:
            DEBUG("OP::ADD");
            j = VM::Pop();
            i = VM::Pop();
            VM::Push(ObjOP::Add(i, j));
            break;
        case OPC::SUB:
            DEBUG("OP::SUB");
            j = VM::Pop();
            i = VM::Pop();
            VM::Push(ObjOP::Sub(i, j));
            break;
        case OPC::EQ:
            DEBUG("OP::EQ");
            j = VM::Pop();
            i = VM::Pop();
            VM::Push(ObjOP::Equal(i,j));
            break;
        case OPC::WHILE:
            DEBUG("OP::WHILE");
            assert(op->HasArgA());
            assert(op->HasArgB());
            VM::ExecCode(co->GetChild(op->GetArgA()));
            while(VM::Pop()->IsTrue()){
                VM::ExecCode(co->GetChild(op->GetArgB()));
                VM::ExecCode(co->GetChild(op->GetArgA()));
            }
            break;
        case OPC::NEQ:
            DEBUG("OP::NEQ");
            j = VM::Pop();
            i = VM::Pop();
            VM::Push(ObjOP::NotEqual(i,j));
            break;
        case OPC::MULT:
            DEBUG("OP::MULT");
            j = VM::Pop();
            i = VM::Pop();
            VM::Push(ObjOP::Mul(i, j));
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
            i = VM::Pop();
            assert(i->GetInt() >= 0);
            co->StoreIDVal(i, op->GetArgA(), op->GetArgB());
            break;
        case OPC::JMP_IF:
            DEBUG("OP::JMP_IF");
            assert(op->HasArgA());
            if(VM::Pop()->IsTrue()) VM::ExecCode(co->GetChild(op->GetArgA()));
            break;
        case OPC::JMP_IF_ELSE:
            DEBUG("OP::JMP_IF_ELSE");
            assert(op->HasArgA());
            //For if, we skip the else statment
            //For else, we skip the if statment
            if(VM::Pop()->IsTrue()) { VM::ExecCode(co->GetChild(op->GetArgA())); op++; }
            else { ++op; VM::ExecCode(co->GetChild(op->GetArgA())); }
            break;
        case OPC::CALL:{
            DEBUG("OP::CALL");
            assert(op->HasArgA());
            assert(op->HasArgB());
            fn = GUARD_CAST<FunctionObj*>(co->GetIDVal(op->GetArgA(), op->GetArgB()));
            if(!fn->IsCFunction()){
                VM::ExecCode(fn->GetObjectCode());
                VM::ResetFlags();
                break;
            }
            //Letting it pass through intended
        }
        case OPC::C_CALL:
        {
            CFunction::Call(fn);
            break;
        }
        case OPC::RETURN:
        {
            DEBUG("OP::RETURN");
            VM::RetFlag = true;
            //TODO, clean the stack
            return;
        }
                         
        default:
            assert(false && "Not Implemented Yet!");
            break;
    }  ++op; //increment the op
    } //end switch, end for
}
