#ifndef T_BOOLEANOBJ_H
#define T_BOOLEANOBJ_H
#include "Object.h"
class BooleanObject : public Object {
public:
  BooleanObject(bool b) : Object(std::make_shared<Value>(b)) {}
  bool isTrue() const { return getBool(); }
  bool isBoolean() { return true; }
  std::string toString();
  SObject operator==(const SObject &rhs);
  static SObject TRUE;
  static SObject FALSE;
};
#endif
