#include "BooleanObj.h"

SObject BooleanObj::TRUE = make_shared<BooleanObj>(true);
SObject BooleanObj::FALSE = make_shared<BooleanObj>(false);
SObject BooleanObj::operator==(const Object* rhs){
    if(IsTrue() == rhs->IsTrue()){
        return TRUE;
    }
    return FALSE;
}

string BooleanObj::ToString(){
    if(IsTrue()) return "TRUE";
    return "False";
}
