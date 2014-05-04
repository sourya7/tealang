#include "CFunction.h"
#include "FunctionObj.h"
#include "IRBuilder.h"
#include "VM.h"

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

void CFunction::Call(FunctionObj* obj){
    GCVecObjPtr p;
    string funcName = obj->GetName();
    FuncSizePair fsp = funcMap[funcName];
    int size = fsp.second;
    while(size--) p.push_back(VM::Pop());
    Object* ret = fsp.first(p);
}

#include <cstdio>
Object* printWrapper(GCVecObjPtr v){
    string s = v.back()->ToString();
    cerr << s;
    //printf(s.c_str());
    return nullptr;
}

Object* printfWrapper(GCVecObjPtr s){
    return nullptr;
}
