#ifndef T_CLASSOBJ_H
#define T_CLASSOBJ_H
#include "Object.h"
#include "CodeObject.h"
class ClassObj : public Object {
private:
    string clsName;
public:  
    ClassObj(string cn, SCodeObj co) : 
                clsName(cn),
                Object(Type::CLASS, MakeShared<Value>(POINTER_VAL(co))){}
    string GetName() { return clsName; }
    SCodeObj GetObjectCode() { return MakeShared<CodeObject>(*(value->co)); }
};
#endif
