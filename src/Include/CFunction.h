#ifndef T_CFUNCTION_H
#define T_CFUNCTION_H

#include <functional>
#include <string>

#include "GC.h"
using namespace std;
class FunctionObj;

Object* printWrapper(GCVecObjPtr s);
Object* printfWrapper(GCVecObjPtr s);

typedef  map<string,FuncSizePair> MapStrFunc;

class IRBuilder;
class CFunction {
public:
    static void Init(IRBuilder* b);
    static void Call(FunctionObj* obj);
};

#endif
