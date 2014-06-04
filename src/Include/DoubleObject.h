#ifndef T_DOUBLEOBJ_H
#define T_DOUBLEOBJ_H
#include "Object.h"
class DoubleObject : public Object {
public:
  DoubleObject(double d) : Object(std::make_shared<Value>(d)) {}
  bool isDouble() { return true; }
  bool isTrue() { return getDouble() != 0; }
  SObject operator+(const SObject &rhs);
  SObject operator*(const SObject &rhs);
  SObject operator-(const SObject &rhs);
  static double getValue(SObject &val) { return val->getDouble(); }
};
#endif
