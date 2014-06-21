#include "Modules/MathModule.h"
#include "Objects/IntegerObject.h"
#include <cmath>

MathModule::MathModule() : Module("Math") {
  MapStrFunc initMap = { { "sqrt:", BIND_INIT_F(MathModule::sqrt, 1) } };
  setInitMap(initMap);
}

SObject MathModule::sqrt(const VecSObject &obj) {
  auto num = obj.back()->getInt();
  //todo need to implemnet it as double once that is done
  long sqrtAsInt = ::sqrt(num);
  auto numObj = std::make_shared<IntegerObject>(sqrtAsInt);
  return numObj;
}

