#ifndef T_BOOLEANOBJ_H
#define T_BOOLEANOBJ_H
#include "Object.h"
class BooleanObj : public Object {
public:  
    BooleanObj(bool b) : Object(TType::BOOLEAN,new TValue(b)) {}
    bool IsTrue() { return GetValue()->b; }  
    bool IsBoolean() { return true; }
    Object* operator+(Object rhs);
    Object* operator*(Object rhs);
    Object* operator-(Object rhs);
};
#endif
