#include "StringObj.h"
#include "BooleanObj.h"

SObject StringObj::operator+(SObject rhs){
    string x = ToString();
    string y = rhs->ToString();
    return MakeShared<StringObj>((x+y).c_str());
}

string StringObj::ToString() { 
    const char* s = value->s;
    return s;
}

SObject StringObj::operator==(SObject rhs){
    return ToString().compare(rhs->ToString()) == 0 ? 
        BooleanObj::TRUE : BooleanObj::FALSE;
}
