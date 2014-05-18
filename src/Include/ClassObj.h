#ifndef T_CLASSOBJ_H
#define T_CLASSOBJ_H
#include "Object.h"
#include "CodeObject.h"
class ClassObj : public Object {
private:
    string clsName;
    SCodeObj co;
public:  
    ClassObj(string cn, SCodeObj o) : 
                clsName(cn), co(o),
                Object(Type::CLASS, MakeShared<Value>(POINTER_VAL(o))){}
    string GetName() { return clsName; }
};
#endif
