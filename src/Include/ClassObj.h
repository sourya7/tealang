#ifndef T_CLASSOBJ_H
#define T_CLASSOBJ_H
#include "Object.h"
#include "CodeObject.h"
class ClassObj : public Object {
private:
    string clsName;
    SCodeObj co;
    bool isInstance = false;
public:  
    ClassObj(string cn, SCodeObj o, bool i = false) : 
                clsName(cn), co(o), isInstance(i),
                Object(Type::CLASS, MakeShared<Value>(POINTER_VAL(o))){}
    string GetName() const { return clsName; }
    bool IsInstance() const { return isInstance; }
};
#endif
