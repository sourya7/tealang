#include "Modules/ListModule.h"
#include "IntegerObj.h"

// register the module.. TODO: A better way?
//

SObject ListModule::Init(const VecSObj &obj) {
  auto instptr = new ListModule();
  auto inst = WRAP_PTR<ListModule>(instptr);
  MapStrFunc funcMap = {
    { "append:", BIND_METH_F(ListModule::Append, inst.get(), 1) },
    { "append:WithKey:", BIND_METH_F(ListModule::Append, inst.get(), 2) },
    { "count", BIND_METH_F(ListModule::Count, inst.get(), 0) },
    { "at:", BIND_METH_F(ListModule::Get, inst.get(), 1) },
    { "reverse", BIND_METH_F(ListModule::Reverse, inst.get(), 0) },
    { "insertVal:At:", BIND_METH_F(ListModule::Insert, inst.get(), 2) }
  };
  inst->SetFuncMap(funcMap);
  inst->SetInstance();
  if(obj.size() > 0){
    inst->_container = obj;
  }
  return inst;
}

ListModule::ListModule() : Module("List") {
  MapStrFunc initMap = { { "init", BIND_INIT_F(ListModule::Init, 0) } };
  SetInitMap(initMap);
}

SObject ListModule::Append(const VecSObj &obj) {
  _container.push_back(obj.back());
  return nullptr;
}

SObject ListModule::Count(const VecSObj &obj) {
  auto size = static_cast<long>(_container.size());
  return MakeShared<IntegerObj>(size);
}

SObject ListModule::Get(const VecSObj &obj) { 
  return _container[IntegerObj::ValFromObj(obj.back())];
}

SObject ListModule::Reverse(const VecSObj &obj) { return nullptr; }

SObject ListModule::Insert(const VecSObj &obj) { return nullptr; }

