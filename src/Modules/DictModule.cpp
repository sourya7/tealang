#include "Modules/DictModule.h"
#include "Objects/IntegerObject.h"
#include "Objects/StringObject.h"

SObject DictModule::init(const VecSObject &obj) {
  auto inst = std::make_shared<DictModule>();
  MapStrFunc funcMap = {
    { "append:WithKey:", BIND_METH_F(DictModule::append, inst.get(), 2) },
    { "size", BIND_METH_F(DictModule::count, inst.get(), 0) },
    { "at:", BIND_METH_F(DictModule::get, inst.get(), 1) },
    { "insertVal:At:", BIND_METH_F(DictModule::insert, inst.get(), 2) }
  };
  inst->setFuncMap(funcMap);
  inst->setInstance();
  return inst;
}

SObject DictModule::initInternal() {
  VecSObject obj;
  return init(obj);
}

DictModule::DictModule() : Module("Dict") {
  MapStrFunc initMap = { { "init", BIND_INIT_F(DictModule::init, 0) } };
  setInitMap(initMap);
}

SObject DictModule::append(const VecSObject &obj) {
  auto key = obj.at(obj.size() - 1);
  auto value = obj.at(obj.size() - 2);
  container_[key] = value;
  return nullptr;
}

SObject DictModule::count(const VecSObject &obj) {
  auto size = static_cast<long>(container_.size());
  return std::make_shared<IntegerObject>(size);
}

SObject DictModule::get(const VecSObject &obj) {
  auto it = container_.find(obj.back());
  assert(it != container_.end());
  return it->second;
}

SObject DictModule::insert(const VecSObject &obj) { return nullptr; }
