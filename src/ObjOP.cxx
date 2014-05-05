#include "ObjOP.h"
namespace ObjOP {
Object* Add(Object* a, Object* b){ 
    Object* ob = *a + b;
    return ob; 
}
Object* Sub(Object* a, Object* b){
    Object* ob = *a - b;
    return ob;
}
Object* Mul(Object* a, Object* b){
    Object* ob = *a * b;
    return ob;
}
Object* Equal(Object* a, Object* b){
    Object* ob = *a == b;
    return ob;
}

Object* NotEqual(Object* a, Object* b){
    Object* ob = *a != b;
    return ob;
}

}
