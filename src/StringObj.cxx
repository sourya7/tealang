#include "StringObj.h"
#include "BooleanObj.h"

SObject StringObj::operator+(const SObject& rhs) {
  string x = ToString();
  string y = rhs->ToString();
  return MakeShared<StringObj>(x + y);
}

string StringObj::ToString() { return GetString(); }

SObject StringObj::operator==(const SObject& rhs) {
  return ToString().compare(rhs->ToString()) == 0 ? BooleanObj::TRUE
                                                  : BooleanObj::FALSE;
}
