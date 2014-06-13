#include "BooleanObject.h"

SObject BooleanObject::TRUE = std::make_shared<BooleanObject>(true);
SObject BooleanObject::FALSE = std::make_shared<BooleanObject>(false);
SObject BooleanObject::operator==(const SObject &rhs) {
  if (isTrue() == rhs->isTrue()) {
    return TRUE;
  }
  return FALSE;
}

std::string BooleanObject::toString() {
  if (isTrue())
    return "TRUE";
  return "FALSE";
}
