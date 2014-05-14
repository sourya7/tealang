#ifndef T_BOOLEANOBJ_H
#define T_BOOLEANOBJ_H
#include "Object.h"
class BooleanObj : public Object {
public:  
    BooleanObj(bool b) : Object(Type::BOOLEAN,MakeShared<Value>(b)) {}
    bool IsTrue() const { return GetValue()->b; }  
    bool IsBoolean() { return true; }
    string ToString();
    SObject operator==(SObject rhs);
    static SObject TRUE;
    static SObject FALSE;
};
#endif
