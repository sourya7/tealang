#ifndef T_STRINGOBJ_H
#define T_STRINGOBJ_H
#include <string>
#include "Object.h"
class StringObject : public Object {
public:
  StringObject(std::string str) : Object(std::make_shared<Value>(str)) {}
  bool isString() { return true; }
  SObject operator+(const SObject &rhs);
  SObject operator==(const SObject &rhs);
  std::string toString();
};
#endif
