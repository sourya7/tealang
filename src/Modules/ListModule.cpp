#include "Modules/ListModule.h"
#include "Objects/IntegerObject.h"

// register the module.. TODO: A better way?
//

SObject ListModule::init(const VecSObject &obj) {
  auto inst = std::make_shared<ListModule>();
  MapStrFunc funcMap = {
    { "append:", BIND_METH_F(ListModule::append, inst.get(), 1) },
    { "append:WithKey:", BIND_METH_F(ListModule::append, inst.get(), 2) },
    { "count", BIND_METH_F(ListModule::count, inst.get(), 0) },
    { "at:", BIND_METH_F(ListModule::get, inst.get(), 1) },
    { "reverse", BIND_METH_F(ListModule::reverse, inst.get(), 0) },
    { "insertVal:At:", BIND_METH_F(ListModule::insert, inst.get(), 2) }
  };
  inst->setFuncMap(funcMap);
  inst->setInstance();
  if (obj.size() > 0) {
    inst->container_ = obj;
  }
  return inst;
}

ListModule::ListModule() : Module("List") {
  MapStrFunc initMap = { { "init", BIND_INIT_F(ListModule::init, 0) } };
  setInitMap(initMap);
}

SObject ListModule::append(const VecSObject &obj) {
  container_.push_back(obj.back());
  return nullptr;
}

SObject ListModule::count(const VecSObject &obj) {
  auto size = static_cast<long>(container_.size());
  return std::make_shared<IntegerObject>(size);
}

SObject ListModule::get(const VecSObject &obj) {
  return container_[IntegerObject::getValue(obj.back())];
}

SObject ListModule::reverse(const VecSObject &obj) { return nullptr; }

SObject ListModule::insert(const VecSObject &obj) { return nullptr; }
