#include "DoubleObj.h"

#define RET_MS_D return MakeShared<DoubleObj>(rhs->GetDouble()); 
SObject DoubleObj::operator+(const SObject& rhs) { RET_MS_D; }

SObject DoubleObj::operator*(const SObject& rhs) { RET_MS_D; }

SObject DoubleObj::operator-(const SObject& rhs) { RET_MS_D; }
