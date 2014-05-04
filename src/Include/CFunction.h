#ifndef T_CFUNCTION_H
#define T_CFUNCTION_H

#include <functional>
#include <string>

#include "gc.h"
using namespace std;
class FunctionObj;

Object* printWrapper(GCVecObjPtr s);
Object* printfWrapper(GCVecObjPtr s);

class IRBuilder;
class CFunction {
public:
    static void Init(IRBuilder* b);
    static void Call(FunctionObj* obj);
};

#endif
