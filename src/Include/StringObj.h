#ifndef T_STRINGOBJ_H
#define T_STRINGOBJ_H
#include "Object.h"
class StringObj : public Object {
    const char* value;
public:  
    StringObj(const char* v) : Object(TType::STRING, new TValue(v)) {}
    bool IsString() { return true; }
    Object* operator+(Object rhs);
    Object* operator*(Object rhs);
    Object* operator-(Object rhs);
};
#endif
