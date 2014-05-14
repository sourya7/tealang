#ifndef T_CFUNCTION_H
#define T_CFUNCTION_H

#include <functional>
#include <string>

#include "GC.h"
using namespace std;
class FunctionObj;

SObject printWrapper(const VecSObj& s);
SObject printfWrapper(const VecSObj& s);

class IRBuilder;
class CFunction {
public:
    static void Init(SIRBuilder b);
    static void Call(SFunctionObj obj);
};

#endif
