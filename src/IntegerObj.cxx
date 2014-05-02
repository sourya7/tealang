#include "IntegerObj.h"
#include "DoubleObj.h"

#define PERFORM_OP(op)\
    if(rhs.IsDouble())\
        return new DoubleObj(value->l op DoubleObj::ValFromObj(rhs));\
    else\
        return new IntegerObj(value->l op IntegerObj::ValFromObj(rhs));\

        
Object* IntegerObj::operator+(Object rhs){
    PERFORM_OP(+)
}

Object* IntegerObj::operator*(Object rhs){
    PERFORM_OP(*)
}

Object* IntegerObj::operator-(Object rhs){
    PERFORM_OP(-)
}

