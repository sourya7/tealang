#ifndef T_BOOLEANOBJ_H
#define T_BOOLEANOBJ_H
#include "Object.h"
class BooleanObj : public Object {
public:  
    BooleanObj(bool b) : Object(TType::BOOLEAN,new TValue(b)) {}
    bool IsTrue() { return GetValue()->b; }  
    bool IsBoolean() { return true; }
    string ToString();
    Object* operator==(Object* rhs);
    static Object* const TRUE;
    static Object* const FALSE;
};
#endif
