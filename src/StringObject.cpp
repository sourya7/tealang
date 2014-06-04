#include "StringObject.h"
#include "BooleanObject.h"

SObject StringObject::operator+(const SObject &rhs) {
  std::string x = toString();
  std::string y = rhs->toString();
  return std::make_shared<StringObject>(x + y);
}

std::string StringObject::toString() { return getString(); }

SObject StringObject::operator==(const SObject &rhs) {
  return toString().compare(rhs->toString()) == 0 ? BooleanObject::TRUE
                                                  : BooleanObject::FALSE;
}
