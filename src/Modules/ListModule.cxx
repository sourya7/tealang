#include "ListModule.h"

//register the module.. TODO: A better way? 
SObject ListModule::Init(const VecSObj &obj) {
  auto instptr = new ListModule();
  auto inst = WRAP_PTR<ListModule>(instptr);
  ModuleFuncMap funcMap = {
    { "append:", BIND_FUNC(ListModule::Append, inst.get()) },
    { "append:WithKey:", BIND_FUNC(ListModule::Append, inst.get()) },
    { "count", BIND_FUNC(ListModule::Count, inst.get()) },
    { "getValAt:", BIND_FUNC(ListModule::Get, inst.get()) },
    { "reverse", BIND_FUNC(ListModule::Reverse, inst.get()) },
    { "insertVal:At:", BIND_FUNC(ListModule::Insert, inst.get()) }
  };
  inst->SetFuncMap(funcMap);
  return inst;
}

SObject ListModule::Append(const VecSObj &obj) {
  return nullptr;
}

SObject ListModule::Count(const VecSObj &obj) {
  return nullptr;
}

SObject ListModule::Get(const VecSObj &obj) { return nullptr; }

SObject ListModule::Reverse(const VecSObj &obj) { return nullptr; }

SObject ListModule::Insert(const VecSObj &obj) { return nullptr; }

