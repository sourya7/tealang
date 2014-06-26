#include "Modules/ListModule.h"
#include "Objects/IntegerObject.h"
#include "Objects/StringObject.h"


/*
 * var list = {1,2,3,4,6]
 * var listIter = [list __iter__] 
 */
SObject ListModule::getIterator(const VecSObject &obj){
  auto iterator = std::make_shared<ListIterator>(&container_); 
  return iterator;
}

SObject ListModule::init(const VecSObject &obj) {
  auto inst = std::make_shared<ListModule>();
  MapStrFunc funcMap = {
    { "append:", BIND_METH_F(ListModule::append, inst.get(), 1) },
    { "size", BIND_METH_F(ListModule::count, inst.get(), 0) },
    { "at:", BIND_METH_F(ListModule::get, inst.get(), 1) },
    { "reverse", BIND_METH_F(ListModule::reverse, inst.get(), 0) },
    { "insertVal:At:", BIND_METH_F(ListModule::insert, inst.get(), 2) },
    { "__iter__", BIND_METH_F(ListModule::getIterator, inst.get(), 0) }
  };
  /*
  MapStrProp propMap = {
    { "__iter__", std::make_shared<ListIterator>(&(inst->container_))}
  }
  */
  inst->setFuncMap(funcMap);
  inst->setInstance();
  if (obj.size() > 0) {
    inst->container_ = obj;
  }
  return inst;
}

SObject ListModule::initInternal() {
  VecSObject obj;
  return init(obj);
}

SObject ListModule::fromStringArray(int count, char *arr[]) {
  VecSObject obj;
  for (int i = 0; i < count; i++) {
    obj.push_back(std::make_shared<StringObject>(arr[i]));
  }
  return init(obj);
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
  size_t index = IntegerObject::getValue(obj.back());
  assert(index < container_.size() && "Index larger that what is inside");
  return container_[IntegerObject::getValue(obj.back())];
}

SObject ListModule::reverse(const VecSObject &obj) { return nullptr; }

SObject ListModule::insert(const VecSObject &obj) { return nullptr; }
