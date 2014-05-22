#include "Debug.h"
#include "VM.h"
#include "ObjOP.h"
#include "Frame.h"
#include "OPCode.h"
#include "ClassObj.h"
#include "CFunction.h"
#include "CodeObject.h"
#include "FunctionObj.h"

#define INCR_OP() (*opid)++;
#define BIN_OP(op)                                                             \
  j = VM::Pop();                                                               \
  i = VM::Pop();                                                               \
  VM::Push(*i op j);

VecSObj VM::vmStack;
VecSCodeObj VM::coStack;
VecPairVecOPInt VM::opsStack;

SInt VM::opid;
SVecOP VM::ops;
SCodeObj VM::co;

void VM::PopCO() {
  coStack.pop_back();
  opsStack.pop_back();
  if (coStack.empty())
    return;
  co = coStack.back();
  ops = opsStack.back().first;
  opid = opsStack.back().second;
}

SObject VM::Pop() {
  SObject top = vmStack.back();
  vmStack.pop_back();
  return top;
}

void VM::Push(SObject a) { vmStack.push_back(a); }

void VM::PushCO(SCodeObj c) {
  opid = MakeShared<int>(0);
  co = c;
  ops = c->GetOPS();
  coStack.push_back(co);
  opsStack.push_back(make_pair(ops, opid));
}

void VM::ExecCode(SCodeObj c) {
  VM::PushCO(c);
  // TODO, if coStack is empty, push a NIL object
  // This is in case the user tries to assign a value to a void function call
  while (!coStack.empty()) {
    if (*opid >= static_cast<int>(ops->size())) {
      PopCO();
      continue;
    }
    SObject i;
    SObject j;
    OP op = (*ops)[*opid];
    OPC opc = op.opc;
    switch (opc) {
    case OPC::ADD:
      DEBUG("OP::ADD");
      BIN_OP(+);
      break;
    case OPC::SUB:
      DEBUG("OP::SUB");
      BIN_OP(-);
      break;
    case OPC::LT:
      DEBUG("OP::LT");
      BIN_OP(< );
      break;
    case OPC::GT:
      DEBUG("OP::GT");
      BIN_OP(> );
      break;
    case OPC::LEQ:
      DEBUG("OP::LEQ");
      BIN_OP(<= );
      break;
    case OPC::GEQ:
      DEBUG("OP::GEQ");
      BIN_OP(>= );
      break;
    case OPC::EQ:
      DEBUG("OP::EQ");
      BIN_OP(== );
      break;
    case OPC::NEQ:
      DEBUG("OP::NEQ");
      BIN_OP(!= );
      break;
    case OPC::MULT:
      DEBUG("OP::MULT");
      BIN_OP(*);
      break;
    // case OPC::POWER: DEBUG("OP::POWER"); BIN_OP(**); break;
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
    case OPC::JMP_IF_ELSE:
      DEBUG("OP::JMP_IF_ELSE");
      INCR_OP();
      assert(op.HasArgA());
      if (VM::Pop()->IsTrue()) {
        SCodeObj ic = co->GetChild(op.GetArgA());
        ic->SetParent(co);
        PushCO(ic);
      } else {
        if (op.HasArgB()) {
          SCodeObj ec = co->GetChild(op.GetArgB());
          ec->SetParent(co);
          PushCO(ec);
        }
      }
      continue;
    case OPC::INIT_INSTANCE: {
      auto classCo = co->GetParent();
      auto classO = MakeShared<ClassObj>(classCo);
      VM::Push(classO);
      break;
    }
    case OPC::CALL_METHOD: {
      DEBUG("OP::CALL_METHOD");
      INCR_OP();
      auto method = VM::Pop();
      auto clsObj = DYN_GC_CAST<ClassObj>(VM::Pop());
      auto clsCo = clsObj->GetCodeObject();
      auto fnId = clsCo->GetID(method->ToString());
      assert(fnId != -1);
      auto fn = DYN_GC_CAST<FunctionObj>(clsCo->GetIDVal(fnId));
      auto fnCo = fn->GetCodeObject(clsCo);
      if (fnCo->IsInit()) {
        assert(!clsObj->IsInstance());
        auto initCo = MakeShared<CodeObject>(*clsCo);
        fnCo->SetParent(initCo);
      } else {
        assert(clsObj->IsInstance());
      }
      PushCO(fnCo);
      continue;
    }
    case OPC::CALL: {
      DEBUG("OP::CALL");
      assert(op.HasArgA());
      assert(op.HasArgB());
      auto fn =
          DYN_GC_CAST<FunctionObj>(co->GetIDVal(op.GetArgA(), op.GetArgB()));
      if (!fn->IsCFunction()) {
        SCodeObj cc = fn->GetCodeObject();
        INCR_OP();
        PushCO(cc);
        continue;
      } else {
        DEBUG("OP::C_CALL");
        fn = DYN_GC_CAST<FunctionObj>(co->GetIDVal(op.GetArgA(), op.GetArgB()));
        CFunction::Call(fn);
      }
      break;
    }
    case OPC::RETURN: {
      // TODO, clean the stack
      assert(op.HasArgA());
      DEBUG("OP::RETURN");
      while (!co->IsFunction()) {
        PopCO();
      }
      PopCO();
      continue;
    }

    default:
      assert(false && "Not Implemented Yet!");
      break;
    }
    INCR_OP(); // increment the op
  }            // end switch, end for
}
