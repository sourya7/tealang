#ifndef T_NUM_H
#define T_NUM_H
#include "Debug.h"
#include "Object.h"

/*
 * TODO: user operator overloading instead for some
 * of the operations
 */
namespace ObjOP {
SObject Add(SObject a, SObject b);
SObject Sub(SObject a, SObject b);
SObject Mul(SObject a, SObject b);
SObject Equal(SObject a, SObject b);
}

#endif
