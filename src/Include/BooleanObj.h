#ifndef T_BOOLEANOBJ_H
#define T_BOOLEANOBJ_H
#include "Object.h"
class BooleanObj : public Object {
    bool value;
public:  
    BooleanObj(bool b) : Object(TType::BOOLEAN,new TValue(b)) {}
    bool IsBoolean() { return true; }
    Object* operator+(Object rhs);
    Object* operator*(Object rhs);
    Object* operator-(Object rhs);
};
#endif
