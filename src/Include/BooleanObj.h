#ifndef T_BOOLEANOBJ_H
#define T_BOOLEANOBJ_H
#include "Object.h"
class BooleanObj : public Object {
public:
  BooleanObj(bool b) : Object(MakeShared<Value>(b)) {}
  bool IsTrue() const { return GetBool(); }
  bool IsBoolean() { return true; }
  string ToString();
  SObject operator==(const SObject& rhs);
  static SObject TRUE;
  static SObject FALSE;
};
#endif
