#include "Modules/IntegerModule.h"
#include "Objects/IntegerObject.h"
#include "Common.h"
#include <string>

IntegerModule::IntegerModule() : Module("IO") {
  MapStrFunc funcMap = { { "fromStr:", BIND_INIT_F(IntegerModule::fromStr, 1) },
                         { "fromNum:", BIND_INIT_F(IntegerModule::fromNum, 1) } };
  setInitMap(funcMap);
}

SObject IntegerModule::fromStr(const VecSObject &v) {
  auto obj = v.back();
  long num = com::fromStr(obj->toString());
  return std::make_shared<IntegerObject>(num);
}

SObject IntegerModule::fromNum(const VecSObject &v) {
  auto obj = v.back();
  return std::make_shared<IntegerObject>(obj->getInt());
}

