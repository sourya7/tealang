#ifndef T_CFUNCTION_H
#define T_CFUNCTION_H

#include <functional>
#include <string>

#include "gc.h"
#include "Object.h"
using namespace std;

Object* printWrapper(GCVecObjPtr s);
Object* printfWrapper(GCVecObjPtr s);

class IRBuilder;
class CFunction {
public:
    static void Init(IRBuilder* b);
    static void Call(Object* obj);
};

#endif
