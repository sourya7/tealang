#ifndef T_BOOLEANOBJ_H
#define T_BOOLEANOBJ_H
#include "Object.h"
class FunctionObj : public Object {
private:
    int argc;
    string funcName;
public:  
    FunctionObj(string fn, int ac, CodeObject* co) : 
                argc(ac), funcName(fn),
                Object(TType::FUNCTION,new TValue(co)){}
    bool IsFunction() { return true; }
    CodeObject* GetObjectCode() { return value->co; }
};
#endif
