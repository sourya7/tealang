#include "StringObj.h"
#include "BooleanObj.h"

Object* StringObj::operator+(Object* rhs){
    string x = ToString();
    string y = rhs->ToString();
    return new StringObj((x+y).c_str());
}

string StringObj::ToString() { 
    const char* s = value->s;
    return s;
}

Object* StringObj::operator==(Object* rhs){
    return ToString().compare(rhs->ToString()) == 0 ? 
        BooleanObj::TRUE : BooleanObj::FALSE;
}
