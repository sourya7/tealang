#include "IntegerObj.h"
#include "BooleanObj.h"
#include "DoubleObj.h"
#include "Common.h"

#define PERFORM_OP(op)\
    if(rhs->IsDouble())\
        return MakeShared<DoubleObj>(GetInt() op rhs->GetDouble());\
    else\
        return MakeShared<IntegerObj>(GetInt() op rhs->GetInt());\

        
SObject IntegerObj::operator+(SObject rhs){
    PERFORM_OP(+)
}

SObject IntegerObj::operator*(SObject rhs){
    PERFORM_OP(*)
}

SObject IntegerObj::operator-(SObject rhs){
    PERFORM_OP(-)
}

SObject IntegerObj::operator==(SObject rhs){
    return GetInt() == rhs->GetInt() ? BooleanObj::TRUE : BooleanObj::FALSE;
}

SObject IntegerObj::operator!=(SObject rhs){
    auto ret = GetInt() != rhs->GetInt() ? BooleanObj::TRUE : BooleanObj::FALSE;
    return ret;
}

string IntegerObj::ToString() {
    long val = value->l;
    string str = COM::toStr(val);
    return str;
}
