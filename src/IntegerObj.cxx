#include "IntegerObj.h"
#include "DoubleObj.h"
#include "Common.h"

#define PERFORM_OP(op)\
    if(rhs->IsDouble())\
        return new DoubleObj(GetInt() op rhs->GetDouble());\
    else\
        return new IntegerObj(GetInt() op rhs->GetInt());\

        
Object* IntegerObj::operator+(Object* rhs){
    PERFORM_OP(+)
}

Object* IntegerObj::operator*(Object* rhs){
    PERFORM_OP(*)
}

Object* IntegerObj::operator-(Object* rhs){
    PERFORM_OP(-)
}

string IntegerObj::ToString() {
    long val = value->l;
    string str = COM::toStr(val);
    return str;
}
