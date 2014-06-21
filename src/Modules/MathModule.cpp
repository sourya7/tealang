#include "Modules/MathModule.h"
#include "Objects/DoubleObject.h"
#include <cmath>

MathModule::MathModule() : Module("Math") {
  MapStrFunc initMap = { { "sqrt:", BIND_INIT_F(MathModule::sqrt, 1) } };
  setInitMap(initMap);
}

SObject MathModule::sqrt(const VecSObject &obj) {
  auto num = obj.back()->getDouble();
  double val = ::sqrt(num);
  auto numObj = std::make_shared<DoubleObject>(val);
  return numObj;
}

