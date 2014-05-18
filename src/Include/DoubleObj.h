#ifndef T_DOUBLEOBJ_H
#define T_DOUBLEOBJ_H
#include "Object.h"
class DoubleObj : public Object {
public:  
    DoubleObj(double d) : Object(MakeShared<Value>(d)) {}
    bool IsDouble() { return true; }
    bool IsTrue() { return GetDouble() != 0; }
    SObject operator+(const Object* rhs);
    SObject operator*(const Object* rhs);
    SObject operator-(const Object* rhs);
    static double ValFromObj(SObject val){ return val->GetDouble(); }
};
#endif
