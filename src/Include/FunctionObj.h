#ifndef T_BOOLEANOBJ_H
#define T_BOOLEANOBJ_H
#include "Object.h"
class FunctionObj : public Object {
private:
    int argc;
    bool isC = false;
    string funcName;
public:  
    FunctionObj(string fn, int ac, CodeObject* co) : 
                argc(ac), funcName(fn),
                Object(TType::FUNCTION,new TValue(co)){}

    FunctionObj(string fn, int ac) : 
                argc(ac), funcName(fn), isC(true),
                Object(TType::FUNCTION){}
    bool IsFunction() { return true; }
    bool IsCFunction() { return isC; }
    string GetName() { return funcName; }
    CodeObject* GetObjectCode() { return value->co; }
};
#endif
