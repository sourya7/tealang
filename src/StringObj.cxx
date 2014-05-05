#include "StringObj.h"

Object* StringObj::operator+(Object* rhs){
    string x = ToString();
    string y = rhs->ToString();
    return new StringObj((x+y).c_str());
}

string StringObj::ToString() { 
    const char* s = value->s;
    return s;
}
