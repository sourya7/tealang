#include "Objects/IntegerObject.h"
#include "Objects/BooleanObject.h"
#include "Objects/DoubleObject.h"

#define PERFORM_BIN_OP(op)                                                     \
  if (rhs->isDouble())                                                         \
    return std::make_shared<DoubleObject>(getInt() op rhs->getDouble());       \
  else                                                                         \
    return std::make_shared<IntegerObject>(getInt() op rhs->getInt());

#define PERFORM_BOOL_OP(op)                                                    \
  return (getInt() op rhs->getInt()) ? BooleanObject::TRUE                     \
                                     : BooleanObject::FALSE;

SObject IntegerObject::operator+(const SObject &rhs) { PERFORM_BIN_OP(+) }
SObject IntegerObject::operator%(const SObject &rhs) {
  return std::make_shared<IntegerObject>(getInt() % rhs->getInt());
}
SObject IntegerObject::operator*(const SObject &rhs) { PERFORM_BIN_OP(*) }
SObject IntegerObject::operator/(const SObject &rhs) { 
  return std::make_shared<DoubleObject>(getInt() / rhs->getDouble());
}
SObject IntegerObject::operator-(const SObject &rhs) { PERFORM_BIN_OP(-) }
SObject IntegerObject::operator<(const SObject &rhs) { PERFORM_BOOL_OP(< ) }
SObject IntegerObject::operator<=(const SObject &rhs) { PERFORM_BOOL_OP(<= ) }
SObject IntegerObject::operator>(const SObject &rhs) { PERFORM_BOOL_OP(> ) }
SObject IntegerObject::operator>=(const SObject &rhs) { PERFORM_BOOL_OP(>= ) }
SObject IntegerObject::operator==(const SObject &rhs) { PERFORM_BOOL_OP(== ) }
SObject IntegerObject::operator!=(const SObject &rhs) { PERFORM_BOOL_OP(!= ) }

std::string IntegerObject::toString() const {
  long val = getInt();
  std::string str = com::toStr(val);
  return str;
}
