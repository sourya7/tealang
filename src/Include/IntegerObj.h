#ifndef T_INTEGEROBJ_H
#define T_INTEGEROBJ_H
#include "Object.h"
class IntegerObj : public Object {
public:  
    IntegerObj(long l) : Object(TType::INTEGER, new TValue(l)) {}
    bool IsInteger() { return true; }
    bool IsTrue() { return GetValue()->l != 0; }
    Object* operator+(Object rhs);
    Object* operator*(Object rhs);
    Object* operator-(Object rhs);
    static long ValFromObj(Object val){ return val.GetValue()->l; }
};
#endif
