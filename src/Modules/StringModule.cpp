#include "Modules/StringModule.h"
#include "Objects/StringObject.h"
#include "Common.h"

StringModule::StringModule() : Module("String") {
  MapStrFunc funcMap = { { "fromObj:", BIND_INIT_F(StringModule::fromObj, 1) } };
  setInitMap(funcMap);
}

SObject StringModule::fromObj(const VecSObject &v) {
  auto obj = v.back();
  return std::make_shared<StringObject>(obj->toString());
  /*
  std::string str;
  if (obj->isNumeral()) {
    if (obj->isDouble())
      str = com::toStr<double>(obj->getDouble());
    else
      str = com::toStr<int>(obj->getInt());
  }
  return std::make_shared<StringObject>(str);
  */
}
