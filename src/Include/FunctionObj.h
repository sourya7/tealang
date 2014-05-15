#ifndef T_FUNCTIONOBJ_H
#define T_FUNCTIONOBJ_H
#include "Object.h"
#include "CodeObject.h"
class FunctionObj : public Object {
private:
    int argc;
    bool isC = false;
    string funcName;
public:  
    FunctionObj(string fn, int ac, SCodeObj co) : 
                argc(ac), funcName(fn),
                Object(Type::FUNCTION, MakeShared<Value>(POINTER_VAL(co))){}
    FunctionObj(string fn, int ac) : 
                argc(ac), funcName(fn), isC(true),
                Object(Type::FUNCTION){}
    bool IsCFunction() { return isC; }
    string GetName() { return funcName; }
    SCodeObj GetObjectCode() { return MakeShared<CodeObject>(*(value->co)); }
    SCodeObj GetObjectCode(SCodeObj p) { 
        auto instance = MakeShared<CodeObject>(*(value->co)); 
        instance->SetParent(p);
        return instance;
    }
};
#endif
