#ifndef T_INTEGEROBJ_H
#define T_INTEGEROBJ_H
#include "Object.h"
class IntegerObject : public Object {
public:
  IntegerObject(long l) : Object(std::make_shared<Value>(l)) {}
  bool isInteger() const { return true; }
  bool isTrue() const { return getInt() != 0; }
  SObject operator+(const SObject &rhs);
  SObject operator%(const SObject &rhs);
  SObject operator/(const SObject &rhs);
  SObject operator<(const SObject &rhs);
  SObject operator<=(const SObject &rhs);
  SObject operator>(const SObject &rhs);
  SObject operator>=(const SObject &rhs);
  SObject operator*(const SObject &rhs);
  SObject operator-(const SObject &rhs);
  SObject operator==(const SObject &rhs);
  SObject operator!=(const SObject &rhs);
  static long getValue(const SObject &val) { return val->getInt(); }
  std::string toString() const;
};
#endif
