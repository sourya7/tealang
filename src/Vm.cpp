#include "Debug.h"
#include "Vm.h"
#include "Module.h"
#include "OpCode.h"
#include "Objects/IntegerObject.h"
#include "Objects/FunctionObject.h"
#include "Objects/ClassObject.h"
#include "CodeObject.h"

#define VM_POP()                                                               \
  vmStack_.back();                                                             \
  vmStack_.pop_back();
#define VM_PUSH(v) vmStack_.push_back(v);

#define INCR_OP() (*opId_)++;
#define BIN_OP(op)                                                             \
  j = VM_POP();                                                                \
  i = VM_POP();                                                                \
  VM_PUSH(*i op j);

VecSObject Vm::vmStack_;
VecSCodeObject Vm::coStack_;
VecPairSVecOpSInt Vm::opsStack_;

SInt Vm::opId_;
SVecOp Vm::vecOp_;
SCodeObject Vm::codeObject_;

void Vm::callModule(const SObject &instance, const SObject &funcName) {
  auto module = std::dynamic_pointer_cast<Module>(instance);
  auto size = module->getArgc(funcName);
  VecSObject p;
  while (size--) {
    auto v = VM_POP();
    p.push_back(v);
  }
  auto ob = Module::call(instance, funcName, p);
  if (ob != nullptr) {
    VM_PUSH(ob);
  }
}

void Vm::getMethodProp(const SObject &instance, const SObject &propName) {
  if (instance->getType() == Type::MODULE) {
    return;
    // do something about it
  }
  auto clsObj = std::dynamic_pointer_cast<ClassObject>(instance);
  auto classCo = clsObj->getCodeObject();
  int id = classCo->getId(propName->toString());
  assert(id != -1);
  auto value = classCo->getIdValue(id);
  VM_PUSH(value);
}

void Vm::callMethod(const SObject &instance, const SObject &funcName) {
  if (instance->getType() == Type::MODULE) {
    Vm::callModule(instance, funcName);
    return;
  }
  auto clsObj = std::dynamic_pointer_cast<ClassObject>(instance);
  auto clsCo = clsObj->getCodeObject();
  auto fnId = clsCo->getId(funcName->toString());
  assert(fnId != -1 && "No function with such name!");
  auto fn = std::dynamic_pointer_cast<FunctionObject>(clsCo->getIdValue(fnId));
  auto fnCo = fn->getCodeObject(clsCo);
  if (fn->isInit()) {
    assert(!clsObj->isInstance());
    auto initCo = std::make_shared<CodeObject>(*clsCo);
    fnCo->setParent(initCo);
  } else {
    assert(clsObj->isInstance());
  }
  pushCodeObject(fnCo);
}

void Vm::callFunc(const SObject &fnob) {
  // TODO, verify if no need for the cast. Normal objects have getCodeObject
  auto fn = std::dynamic_pointer_cast<FunctionObject>(fnob);
  SCodeObject cc = fn->getCodeObject();
  pushCodeObject(cc);
}

void Vm::popCodeObject() {
  coStack_.pop_back();
  opsStack_.pop_back();
  if (coStack_.empty())
    return;
  codeObject_ = coStack_.back();
  auto opsBack = opsStack_.back();
  vecOp_ = opsBack.first;
  opId_ = opsBack.second;
}

void Vm::pushCodeObject(const SCodeObject &c) {
  opId_ = std::make_shared<int>(0);
  codeObject_ = c;
  vecOp_ = c->getOpCode();
  coStack_.push_back(codeObject_);
  opsStack_.push_back(std::make_pair(vecOp_, opId_));
}

void Vm::execCode(const SCodeObject &c) {
  Vm::pushCodeObject(c);
  // TODO, if coStack_ is empty, push a NIL object
  // This is in case the user tries to assign a value to a void function call
  while (!coStack_.empty()) {
    if (*opId_ >= static_cast<int>(vecOp_->size())) {
      popCodeObject();
      continue;
    }
    SObject i;
    SObject j;

    Op op = (*vecOp_)[*opId_];
    Opc opc = op.opc_;
    switch (opc) {
    case Opc::ADD:
      DEBUG("OP::ADD");
      BIN_OP(+);
      break;
    case Opc::SUB:
      DEBUG("OP::SUB");
      BIN_OP(-);
      break;
    case Opc::UNARY_SUB:
      DEBUG("OP::UNARY_SUB");
      i = VM_POP();
      j = std::make_shared<IntegerObject>(0);
      VM_PUSH(*j - i);
      break;
    case Opc::MOD:
      DEBUG("OP::MOD");
      BIN_OP(% );
      break;
    case Opc::LT:
      DEBUG("OP::LT");
      BIN_OP(< );
      break;
    case Opc::GT:
      DEBUG("OP::GT");
      BIN_OP(> );
      break;
    case Opc::LEQ:
      DEBUG("OP::LEQ");
      BIN_OP(<= );
      break;
    case Opc::GEQ:
      DEBUG("OP::GEQ");
      BIN_OP(>= );
      break;
    case Opc::EQ:
      DEBUG("OP::EQ");
      BIN_OP(== );
      break;
    case Opc::AND:
      DEBUG("OP::AND");
      BIN_OP(&&);
      break;
    case Opc::OR:
      DEBUG("OP::OR");
      BIN_OP(|| );
      break;
    case Opc::NEQ:
      DEBUG("OP::NEQ");
      BIN_OP(!= );
      break;
    case Opc::MULT:
      DEBUG("OP::MULT");
      BIN_OP(*);
      break;
    case Opc::DIV:
      DEBUG("OP::DIV");
      BIN_OP(/ );
      break;
    // case Opc::POWER: DEBUG("OP::POWER"); BIN_OP(**); break;
    case Opc::WHILE: {
      DEBUG("OP::WHILE");
      assert(op.hasArgA());
      SCodeObject co = codeObject_->getChild(op.getArgA());
      co->setParent(codeObject_);
      pushCodeObject(co);
      continue;
    }
    /*TODO, Better to not have BREAK and CONTINUE in the vm. */
    case Opc::BREAK:
      DEBUG("OP::BREAK")
      while (codeObject_->getBlockType() != BlockType::WHILE) {
        popCodeObject();
      }
      popCodeObject();
      break;
    case Opc::CONTINUE:
      DEBUG("OP::CONTINUE")
      while (codeObject_->getBlockType() != BlockType::WHILE) {
        popCodeObject();
      }
      opId_ = 0;
      continue;
    case Opc::LOAD_CONSTANT:
      DEBUG("OP::PUSH_CONSTANT");
      assert(op.hasArgA());
      i = codeObject_->getConst(op.getArgA());
      VM_PUSH(i);
      break;
    case Opc::LOAD_VALUE:
      DEBUG("OP::LOAD_VALUE");
      assert(op.hasArgA());
      assert(op.hasArgB());
      i = codeObject_->getIdValue(op.getArgA(), op.getArgB());
      assert(i != nullptr);
      VM_PUSH(i);
      break;
    case Opc::STORE_VALUE:
      DEBUG("OP::STORE_VALUE");
      assert(op.hasArgA());
      assert(op.hasArgB());
      i = VM_POP();
      codeObject_->storeIdValue(i, op.getArgA(), op.getArgB());
      break;
    case Opc::JMP_IF_ELSE: {
      DEBUG("OP::JMP_IF_ELSE");
      INCR_OP();
      assert(op.hasArgA());
      auto v = VM_POP();
      if (v->isTrue()) {
        SCodeObject ic = codeObject_->getChild(op.getArgA());
        ic->setParent(codeObject_);
        pushCodeObject(ic);
      } else {
        if (op.hasArgB()) {
          SCodeObject ec = codeObject_->getChild(op.getArgB());
          ec->setParent(codeObject_);
          pushCodeObject(ec);
        }
      }
      continue;
    }
    case Opc::INIT_INSTANCE: {
      auto classCo = codeObject_->getParent();
      auto classO = std::make_shared<ClassObject>(classCo);
      VM_PUSH(classO);
      INCR_OP();
      continue;
    }
    case Opc::CALL_METHOD: {
      DEBUG("OP::CALL_METHOD");
      INCR_OP();
      auto method = VM_POP();
      auto instance = VM_POP();
      Vm::callMethod(instance, method);
      continue;
    }
    case Opc::DOT: {
      DEBUG("OP::DOT");
      i = VM_POP();
      j = VM_POP();
      Vm::getMethodProp(j, i);
      break;
    }
    case Opc::CALL: {
      DEBUG("OP::CALL");
      assert(op.hasArgA());
      assert(op.hasArgB());
      auto fnob = codeObject_->getIdValue(op.getArgA(), op.getArgB());
      INCR_OP();
      Vm::callFunc(fnob);
      continue;
    }
    case Opc::RETURN: {
      // TODO, clean the stack
      assert(op.hasArgA());
      DEBUG("OP::RETURN");
      while (codeObject_->getBlockType() != BlockType::FUNCTION) {
        popCodeObject();
      }
      popCodeObject();
      continue;
    }

    default:
      assert(false && "Not Implemented Yet!");
      break;
    }
    INCR_OP(); // increment the op
  }            // end switch, end for
}
