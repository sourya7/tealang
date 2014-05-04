#include "CFunction.h"
#include "IRBuilder.h"

GCMapStrFunc funcMap = {
    {"printf:", {printWrapper, 1}},
    {"printf:withF:", {printfWrapper, 2}},
};

void CFunction::Init(IRBuilder* b){
    for(auto f : funcMap){
        int argc = f.second.second;
        string funcName = f.first;
        b->DeclCFunc(funcName, argc);
    }
}

void CFunction::Call(Object* obj){
    assert(false);
}

Object* printWrapper(GCVecObjPtr s){
    return nullptr;
}

Object* printfWrapper(GCVecObjPtr s){
    return nullptr;
}
