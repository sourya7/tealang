#ifndef T_STRINGOBJ_H
#define T_STRINGOBJ_H
#include "Object.h"
class StringObj : public Object {
public:  
    StringObj(const char* v) : Object(Type::STRING, make_shared<Value>(v)) {}
    bool IsString() { return true; }
    SObject operator+(Object* rhs);
    SObject operator==(Object* rhs);
    string ToString();
};
#endif
