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
    SCodeObj co;
    bool isC;
public:  
    FunctionObj(string fn, int ac, SCodeObj o) :
                Object(MakeShared<Value>(POINTER_VAL(o))),
                argc(ac),funcName(fn),co(o),isC(false)
                {}
    FunctionObj(string fn, int ac) : 
                Object(MakeShared<Value>((CodeObject*)nullptr)),
                argc(ac),funcName(fn),co(nullptr),isC(true)
                {}
    bool IsCFunction() { return isC; }
    int GetArgc() { return argc; }
    string GetName() { return funcName; }
    SCodeObj GetCodeObject() const { return MakeShared<CodeObject>(*Object::GetCodeObject()); }
    SCodeObj GetCodeObject(SCodeObj o) const { 
        auto instance = GetCodeObject();
        instance->SetParent(o);
        return instance;
    }
};
#endif
