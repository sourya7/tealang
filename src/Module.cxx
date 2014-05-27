#include "Module.h"
#include "IRBuilder.h"

map<string, SModule> Module::_modules;

void LoadModule(const SObject &modulename) {}

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

void Module::LoadDefault(const SIRBuilder &builder) {
  for (auto mpair : _modules) {
    SModule m = mpair.second;
    if (m->_loadDefault) {
      // TODO ->  Make m a weak_ptr before passing it
      builder->DeclVar(m->_moduleName, m);
    }
  }
}

