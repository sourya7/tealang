#include "Debug.h"
#include "VM.h"
#include "ObjOP.h"
#include "Frame.h"
#include "OPCode.h"
#include "CFunction.h"
#include "CodeObject.h"
#include "FunctionObj.h"

VecSObj VM::vmStack;
VecSCodeObj VM::coStack;
VecPairVecOPInt VM::opsStack;
#define INCR_OP() (*opid)++;
SVecOP VM::ops;
SInt VM::opid;
SCodeObj VM::co;

bool VM::RetFlag = false;


void VM::PopCO() {
    coStack.pop_back();
    opsStack.pop_back();
    if(coStack.empty()) return;
    co = coStack.back();
    ops = opsStack.back().first;
    opid = opsStack.back().second;
}

SObject VM::Pop() { 
    SObject top = vmStack.back(); 
    vmStack.pop_back(); 
    return top; 
}

void VM::Push(SObject a) { 
    vmStack.push_back(a); 
}

void VM::PushCO(SCodeObj c) { 
    opid = MakeShared<int>(0);
    co = c;
    ops = c->GetOPS();
    coStack.push_back(co);
    opsStack.push_back(make_pair(ops, opid));
}

void VM::ExecCode(SCodeObj c){
    VM::PushCO(c);
    int count = 30;
    //TODO, if coStack is empty, push a NIL object
    //This is in case the user tries to assign a value to a void function call
    while(!coStack.empty()) {
    if(*opid >= ops->size()) { 
        PopCO(); continue; 
    }

    SObject i;
    SObject j;
    SFunctionObj fn;
    OP op = (*ops)[*opid];
    OPC opc = op.opc;
    switch(opc){
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
            VM::Push(*i - j);
            break;
        case OPC::EQ:
            DEBUG("OP::EQ");
            j = VM::Pop();
            i = VM::Pop();
            VM::Push(*i == j);
            break;
            /*
        case OPC::WHILE:
            DEBUG("OP::WHILE");
            assert(op.HasArgA());
            assert(op.HasArgB());
            assert(false);
            VM::ExecCode(co->GetChild(op.GetArgA()));
            while(VM::Pop()->IsTrue()){
                VM::ExecCode(co->GetChild(op.GetArgB()));
                VM::ExecCode(co->GetChild(op.GetArgA()));
            }
            break;
            */
        case OPC::NEQ:
            DEBUG("OP::NEQ");
            j = VM::Pop();
            i = VM::Pop();
            VM::Push(*i != j);
            break;
        case OPC::MULT:
            DEBUG("OP::MULT");
            j = VM::Pop();
            i = VM::Pop();
            VM::Push(*i * j);
            break;
        case OPC::LOAD_CONSTANT:
            DEBUG("OP::PUSH_CONSTANT");
            assert(op.HasArgA());
            i = co->GetConst(op.GetArgA());
            VM::Push(i);
            break;
        case OPC::LOAD_VALUE:
            DEBUG("OP::LOAD_VALUE");
            assert(op.HasArgA());
            assert(op.HasArgB());
            i = co->GetIDVal(op.GetArgA(), op.GetArgB());
            VM::Push(i);
            break;
        case OPC::STORE_VALUE:
            DEBUG("OP::STORE_VALUE");
            assert(op.HasArgA());
            assert(op.HasArgB());
            i = VM::Pop();
            assert(i->GetInt() >= 0);
            co->StoreIDVal(i, op.GetArgA(), op.GetArgB());
            break;
        case OPC::JMP_IF:
            DEBUG("OP::JMP_IF");
            assert(op.HasArgA());
            if(VM::Pop()->IsTrue()) {
                SCodeObj c = co->GetChild(op.GetArgA());
                c->SetParent(co);
                INCR_OP();
                PushCO(c); 
            } else { INCR_OP(); }
            continue;
        case OPC::JMP_IF_ELSE:
            DEBUG("OP::JMP_IF_ELSE");
            assert(op.HasArgA());
            //For if, we skip the else statment
            //For else, we skip the if statment
            if(VM::Pop()->IsTrue()) { 
                SCodeObj c = co->GetChild(op.GetArgA());
                c->SetParent(co);
                INCR_OP(); //move to the next which is else
                INCR_OP(); //eat up the else statement
                PushCO(c);
            }
            else { 
                INCR_OP(); // consume the previous if
                SCodeObj c = co->GetChild(op.GetArgA());
                c->SetParent(co);
                INCR_OP(); //consume the else stmt
                PushCO(c); 
            }
            continue;
        case OPC::CALL_METHOD:
        {
            DEBUG("OP::CALL");
            auto method = VM::Pop();
            auto instance = VM::Pop();
            auto i_co = instance->GetCodeObject();
            auto fn_id = i_co->GetID(method->ToString());
            assert(fn_id != -1);
            auto fn = DYN_GC_CAST<FunctionObj>(i_co->GetIDVal(fn_id));
            //Todo, make a wrapper that works with gc
            auto fn_co = fn->GetCodeObject(i_co);
            INCR_OP();
            PushCO(fn_co);
            continue;
        }
        case OPC::CALL:{
            DEBUG("OP::CALL");
            assert(op.HasArgA());
            assert(op.HasArgB());
            auto fn = DYN_GC_CAST<FunctionObj>(co->GetIDVal(op.GetArgA(), op.GetArgB()));
            if(!fn->IsCFunction()){
                SCodeObj c = fn->GetCodeObject(); 
                INCR_OP();
                PushCO(c);
                continue;
            }
            //Letting it pass through intended
        }
        case OPC::C_CALL:
        {
            auto fn = DYN_GC_CAST<FunctionObj>(co->GetIDVal(op.GetArgA(), op.GetArgB()));
            CFunction::Call(fn);
            break;
        }
        case OPC::RETURN:
        {
            //TODO, clean the stack
            DEBUG("OP::RETURN");
            while(!co->IsFunction()){
                PopCO();
            }
            PopCO();
            continue;
        }
                         
        default:
            assert(false && "Not Implemented Yet!");
            break;
    }  INCR_OP(); //increment the op
    } //end switch, end for
}
