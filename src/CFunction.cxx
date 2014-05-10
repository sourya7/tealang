#include "CFunction.h"
#include "FunctionObj.h"
#include "IRBuilder.h"
#include "VM.h"

MapStrFunc funcMap = {
    {"printf:", {printWrapper, 1}},
    {"printf:withF:", {printfWrapper, 2}},
};

void CFunction::Init(SIRBuilder b){
    for(auto f : funcMap){
        int argc = f.second.second;
        string funcName = f.first;
        b->DeclCFunc(funcName, argc);
    }
}

void CFunction::Call(SFunctionObj obj){
    VecSObj p;
    string funcName = obj->GetName();
    FuncSizePair fsp = funcMap[funcName];
    int size = fsp.second;
    while(size--) p.push_back(VM::Pop());
    SObject ret = fsp.first(p);
}

SObject printWrapper(const VecSObj& v){
    string s = v.back()->ToString();
    cerr << s;
    return nullptr;
}

SObject printfWrapper(const VecSObj& s){
    return nullptr;
}
