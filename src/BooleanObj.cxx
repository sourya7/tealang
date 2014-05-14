#include "BooleanObj.h"

SObject BooleanObj::TRUE = MakeShared<BooleanObj>(true);
SObject BooleanObj::FALSE = MakeShared<BooleanObj>(false);
SObject BooleanObj::operator==(SObject rhs){
    if(IsTrue() == rhs->IsTrue()){
        return TRUE;
    }
    return FALSE;
}

string BooleanObj::ToString(){
    if(IsTrue()) return "TRUE";
    return "False";
}
