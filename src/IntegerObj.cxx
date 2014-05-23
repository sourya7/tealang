#include "IntegerObj.h"
#include "BooleanObj.h"
#include "DoubleObj.h"
#include "Common.h"

#define PERFORM_BIN_OP(op)                                                     \
  if (rhs->IsDouble())                                                         \
    return MakeShared<DoubleObj>(GetInt() op rhs->GetDouble());                \
  else                                                                         \
    return MakeShared<IntegerObj>(GetInt() op rhs->GetInt());

#define PERFORM_BOOL_OP(op)                                                    \
  return (GetInt() op rhs->GetInt()) ? BooleanObj::TRUE : BooleanObj::FALSE;

SObject IntegerObj::operator+(const SObject& rhs) { PERFORM_BIN_OP(+) }
SObject IntegerObj::operator*(const SObject& rhs) { PERFORM_BIN_OP(*) }
SObject IntegerObj::operator-(const SObject& rhs) { PERFORM_BIN_OP(-) }
SObject IntegerObj::operator<(const SObject& rhs) { PERFORM_BOOL_OP(< ) }
SObject IntegerObj::operator<=(const SObject& rhs) { PERFORM_BOOL_OP(<= ) }
SObject IntegerObj::operator>(const SObject& rhs) { PERFORM_BOOL_OP(> ) }
SObject IntegerObj::operator>=(const SObject& rhs) { PERFORM_BOOL_OP(>= ) }
SObject IntegerObj::operator==(const SObject& rhs) { PERFORM_BOOL_OP(== ) }
SObject IntegerObj::operator!=(const SObject& rhs) { PERFORM_BOOL_OP(!= ) }

string IntegerObj::ToString() {
  long val = GetInt();
  string str = COM::toStr(val);
  return str;
}
