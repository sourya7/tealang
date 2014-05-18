#ifndef T_STRINGOBJ_H
#define T_STRINGOBJ_H
#include "Object.h"
class StringObj : public Object {
public:  
    StringObj(string s) : Object(MakeShared<Value>(s)) {}
    bool IsString() { return true; }
    SObject operator+(SObject rhs);
    SObject operator==(SObject rhs);
    string ToString();
};
#endif
