#ifndef T_NUM_H
#define T_NUM_H
#include "Debug.h"
#include "Object.h"

/* 
 * TODO: user operator overloading instead for some 
 * of the operations 
 */
namespace ObjOP{
    Object* Add(Object* a, Object* b);
    Object* Sub(Object* a, Object* b);
    Object* Mul(Object* a, Object* b);
    Object* Equal(Object* a, Object* b);
    Object* NotEqual(Object* a, Object* b);
}

#endif
