#include "BooleanObj.h"

Object* const BooleanObj::TRUE = new BooleanObj(true);
Object* const BooleanObj::FALSE = new BooleanObj(false);
Object* BooleanObj::operator==(Object* rhs){
    if(IsTrue() == rhs->IsTrue()){
        return TRUE;
    }
    return FALSE;
}

string BooleanObj::ToString(){
    if(IsTrue()) return "TRUE";
    return "False";
}
