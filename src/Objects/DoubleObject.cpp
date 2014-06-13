#include "Objects/DoubleObject.h"

#define RET_MS_D return std::make_shared<DoubleObject>(rhs->getDouble());
SObject DoubleObject::operator+(const SObject &rhs) { RET_MS_D; }

SObject DoubleObject::operator*(const SObject &rhs) { RET_MS_D; }

SObject DoubleObject::operator-(const SObject &rhs) { RET_MS_D; }
