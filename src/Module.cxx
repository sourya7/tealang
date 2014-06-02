#include "Module.h"
#include "IRBuilder.h"

map<string, SModule> Module::_modules;
SObject Module::Call(const SObject &instance, const SObject &method,
                     const VecSObj &params) {
  SModule mod = GetModuleFromObj(instance);
  if (instance.get() == nullptr) {
    // TODO: static methods don't work currently
    return mod->_initMap[method->ToString()](params);
  } else {
    return mod->_funcMap[method->ToString()](params);
  }
}

void Module::LoadModule(std::string name, const SIRBuilder &builder){
  auto m = _modules[name];
  builder->DeclVar(name, m);
}

void Module::LoadDefaults(const SIRBuilder &builder) {
  LoadModule("List", builder);
  LoadModule("IO", builder);
}

