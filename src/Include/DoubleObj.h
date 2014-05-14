#ifndef T_DOUBLEOBJ_H
#define T_DOUBLEOBJ_H
#include "Object.h"
class DoubleObj : public Object {
public:  
    DoubleObj(double d) : Object(Type::DOUBLE, MakeShared<Value>(d)) {}
    bool IsDouble() { return true; }
    bool IsTrue() { return GetValue()->l != 0; }
    SObject operator+(const Object* rhs);
    SObject operator*(const Object* rhs);
    SObject operator-(const Object* rhs);
    static double ValFromObj(SObject val){ return val->GetValue()->l; }
};
#endif
