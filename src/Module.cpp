#include "Module.h"
#include "IrBuilder.h"

std::map<std::string, SModule> Module::modules_;
SObject Module::call(const SObject &instance, const SObject &method,
                     const VecSObject &params) {
  SModule mod = std::dynamic_pointer_cast<Module>(instance);
  if (!mod->isInstance()) {
    // TODO check if the methods exist
    return mod->initMap_[method->toString()].first(params);
  } else {
    return mod->funcMap_[method->toString()].first(params);
  }
  return nullptr;
}

void Module::loadModule(std::string name, const SIrBuilder &builder) {
  auto m = modules_[name];
  builder->declVar(name, m);
}

int Module::getArgc(const SObject &method) const {
  auto methodName = method->toString();
  auto it = initMap_.find(methodName);
  if (it != initMap_.end()) {
  } else {
    it = funcMap_.find(methodName);
    if (it != funcMap_.end()) {
    } else {
      assert(false && "Calling a method that does not exist");
    }
  }
  return (*it).second.second;
}

bool Module::isKnownModule(std::string moduleName) {
  return modules_.find(moduleName) != modules_.end();
}

void Module::loadDefaults(const SIrBuilder &builder) {
  loadModule("List", builder);
  loadModule("Dict", builder);
  loadModule("String", builder);
  loadModule("Integer", builder);
}
