#include "Modules/StringModule.h"
#include "Objects/StringObject.h"
#include "Objects/IntegerObject.h"
#include "Common.h"

StringModule::StringModule() : Module("String") {
  MapStrFunc funcMap = { { "fromObj:", BIND_INIT_F(StringModule::fromObj, 1) },   
                         { "lengthOf:", BIND_INIT_F(StringModule::length, 1) }, 
                         { "find:In:", BIND_INIT_F(StringModule::find, 1) } };

  setInitMap(funcMap);
}

SObject StringModule::length(const VecSObject &v) {
  return std::make_shared<IntegerObject>(v.back()->toString().size());
}

SObject StringModule::find(const VecSObject &obj) {
  auto key = obj.at(obj.size() - 1)->toString();
  auto value = obj.at(obj.size() - 2)->toString();
  auto found = value.find(key);
  if(found != std::string::npos){
    return std::make_shared<IntegerObject>(static_cast<long>(found));
  }
  return std::make_shared<IntegerObject>(-1);
}


SObject StringModule::fromObj(const VecSObject &v) {
  auto obj = v.back();
  return std::make_shared<StringObject>(obj->toString());
}
