#ifndef T_NUM_H
#define T_NUM_H
#include "Debug.h"
#include "Object.h"

/* 
 * TODO: user operator overloading instead for some 
 * of the operations 
 */
namespace Num {
    Object* Add(Object* a, Object* b){ 
        Object* ob = *a + *b;
        return ob; 
    }
    Object* Sub(Object* a, Object* b){
        Object* ob = *a - *b;
        return ob;
    }
    Object* Mul(Object* a, Object* b){
        Object* ob = *a * *b;
        return ob;
    }
}

#endif
