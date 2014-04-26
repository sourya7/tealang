#ifndef T_TOBJECT_H
#define T_TOBJECT_H
#include "Type.h"
class TObj {
private:
    TValue value;
    TType type;
    
    TObj(TValue v, TType t) : value(v), type(t) {}
    TType GetType() { return type; }
};
#endif
