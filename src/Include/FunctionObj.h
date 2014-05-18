#ifndef T_FUNCTIONOBJ_H
#define T_FUNCTIONOBJ_H
#include "Object.h"
#include "CodeObject.h"
/*
 * TODO: I believe the object class should not have a "CodeObject" value
 * We should only have specific deriving classes like this implement them
 */
class FunctionObj : public Object {
private:
    int argc;
    string funcName;
    SCodeObj co = nullptr;
    bool isC = false;
public:  
    FunctionObj(string fn, int ac, SCodeObj o) : 
                argc(ac), funcName(fn), co(o),
                Object(Type::FUNCTION, MakeShared<Value>(POINTER_VAL(o))){}
    FunctionObj(string fn, int ac) : 
                argc(ac), funcName(fn), isC(true),
                Object(Type::FUNCTION){}
    bool IsCFunction() { return isC; }
    string GetName() { return funcName; }
    SCodeObj GetCodeObject() { return Object::GetCodeObject(); }
    SCodeObj GetCodeObject(SCodeObj o) { 
        auto instance = GetCodeObject();
        instance->SetParent(o);
        return instance;
    }
};
#endif
