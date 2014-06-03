#include "Module.h"
#include "IRBuilder.h"

map<string, SModule> Module::_modules;
SObject Module::Call(const SObject &instance, const SObject &method,
                     const VecSObj &params) {
  SModule mod = GetModuleFromObj(instance);
  if (!mod->IsInstance()) {
    //TODO check if the methods exist
    return mod->_initMap[method->ToString()].first(params);
  } else {
    return mod->_funcMap[method->ToString()].first(params);
  }
  return nullptr;
}

void Module::LoadModule(std::string name, const SIRBuilder &builder){
  auto m = _modules[name];
  builder->DeclVar(name, m);
}

int Module::GetArgc(const SObject &method) const {
  auto methodName = method->ToString();
  auto it = _initMap.find(methodName);
  if(it != _initMap.end()){
  }
  else{
    it = _funcMap.find(methodName);
    if(it != _funcMap.end()){
    }
    else{
      assert(false && "Calling a method that does not exist");
    }
  }
  return (*it).second.second;
}

void Module::LoadDefaults(const SIRBuilder &builder) {
  //LoadModule("List", builder);
  LoadModule("IO", builder);
}

