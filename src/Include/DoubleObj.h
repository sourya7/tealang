#ifndef T_DOUBLEOBJ_H
#define T_DOUBLEOBJ_H
#include "Object.h"
class DoubleObj : public Object {
public:  
    DoubleObj(double d) : Object(TType::DOUBLE, new TValue(d)) {}
    bool IsDouble() { return true; }
    Object* operator+(Object rhs);
    Object* operator*(Object rhs);
    Object* operator-(Object rhs);
    static double ValFromObj(Object val){ return val.GetValue()->l; }
};
#endif
