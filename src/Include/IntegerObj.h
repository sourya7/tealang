#ifndef T_INTEGEROBJ_H
#define T_INTEGEROBJ_H
#include "Object.h"
class IntegerObj : public Object {
public:
  IntegerObj(long l) : Object(MakeShared<Value>(l)) {}
  bool IsInteger() { return true; }
  bool IsTrue() { return GetInt() != 0; }
  SObject operator+(const SObject& rhs);
  SObject operator<(const SObject& rhs);
  SObject operator<=(const SObject& rhs);
  SObject operator>(const SObject& rhs);
  SObject operator>=(const SObject& rhs);
  SObject operator*(const SObject& rhs);
  SObject operator-(const SObject& rhs);
  SObject operator==(const SObject& rhs);
  SObject operator!=(const SObject& rhs);
  static long ValFromObj(const SObject& val) { return val->GetInt(); }
  string ToString();
};
#endif
