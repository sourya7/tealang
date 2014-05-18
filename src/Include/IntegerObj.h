#ifndef T_INTEGEROBJ_H
#define T_INTEGEROBJ_H
#include "Object.h"
class IntegerObj : public Object {
public:  
    IntegerObj(long l) : Object(MakeShared<Value>(l)) {}
    bool IsInteger() { return true; }
    bool IsTrue() { return GetInt() != 0; }
    SObject operator+(SObject rhs);
    SObject operator*(SObject rhs);
    SObject operator-(SObject rhs);
    SObject operator==(SObject rhs);
    SObject operator!=(SObject rhs);
    static long ValFromObj(SObject val){ return val->GetInt(); }
    string ToString();
};
#endif
