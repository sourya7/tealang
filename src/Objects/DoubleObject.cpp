#include "Objects/IntegerObject.h"
#include "Objects/BooleanObject.h"
#include "Objects/DoubleObject.h"

#define RET_MS_D return std::make_shared<DoubleObject>(rhs->getDouble());

#define PERFORM_BIN_OP(op)                                                     \
  if (rhs->isInteger())                                                        \
    return std::make_shared<DoubleObject>(getDouble() op rhs->getInt());       \
  else                                                                         \
    return std::make_shared<DoubleObject>(getDouble() op rhs->getDouble());

#define PERFORM_BOOL_OP(op)                                                    \
  if (rhs->isInteger())                                                        \
    return (getDouble() op rhs->getInt()) ? BooleanObject::TRUE                \
                                          : BooleanObject::FALSE;              \
  else                                                                         \
    return (getDouble() op rhs->getDouble()) ? BooleanObject::TRUE             \
                                             : BooleanObject::FALSE;

SObject DoubleObject::operator+(const SObject &rhs) { PERFORM_BIN_OP(+) }
SObject DoubleObject::operator%(const SObject &rhs) { return std::make_shared<IntegerObject>(getInt() % rhs->getInt()); }
SObject DoubleObject::operator*(const SObject &rhs) { PERFORM_BIN_OP(*) }
SObject DoubleObject::operator-(const SObject &rhs) { PERFORM_BIN_OP(-) }
SObject DoubleObject::operator<(const SObject &rhs) { PERFORM_BOOL_OP(< ) }
SObject DoubleObject::operator<=(const SObject &rhs) { PERFORM_BOOL_OP(<= ) }
SObject DoubleObject::operator>(const SObject &rhs) { PERFORM_BOOL_OP(> ) }
SObject DoubleObject::operator>=(const SObject &rhs) { PERFORM_BOOL_OP(>= ) }
SObject DoubleObject::operator==(const SObject &rhs) { PERFORM_BOOL_OP(== ) }
SObject DoubleObject::operator!=(const SObject &rhs) { PERFORM_BOOL_OP(!= ) }

std::string DoubleObject::toString() const {
  double val = getDouble();
  std::string str = com::toStr(val);
  return str;
}
