#ifndef T_STRINGOBJ_H
#define T_STRINGOBJ_H
#include "Object.h"
class StringObj : public Object {
    const char* c;
public:  
    StringObj(const char* v) : Object(Type::STRING, MakeShared<Value>(v)) { c = v; }
    bool IsString() { return true; }
    SObject operator+(SObject rhs);
    SObject operator==(SObject rhs);
    string ToString();
};
#endif
