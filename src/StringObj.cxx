#include "StringObj.h"

Object* StringObj::operator+(Object rhs){
}

Object* StringObj::operator*(Object rhs){
}

Object* StringObj::operator-(Object rhs){
}

string StringObj::ToString() { 
    const char* s = value->s;
    return s;
}
