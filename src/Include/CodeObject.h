#ifndef T_CODEOBJECT_H
#define T_CODEOBJECT_H

#include <string>
#include "GC.h"
#include "Debug.h"
#include "Object.h"
#include "OPCode.h"

using std::string;
class CodeObject;

enum class CT { FUNCTION, METHOD, NORM };
class CodeObject : public TGC {
private:
    //variables in the codeobject scope
    GCVecString ids;
    //value for those vars
    GCVecObjPtr vals;
    //constants in the codeobject scope
    GCVecObjPtr consts;
    //opcodes for this codeobject
    GCVecOP opcode;
    GCVecCodeObjPtr children;
    CodeObject* parent = nullptr;
    CT type = CT::NORM;
public:
    CodeObject(CodeObject* p) : parent(p) {}
    CodeObject() {}
    int PushID(string var); 
    int PushConst(Object* o);

    int GetID(string var, int &l);
    int GetID(string var) { int l; return GetID(var, l); } 
    void StoreIDVal(Object* val, int id, int level=0);
    Object* GetIDVal(int id, int level=0);

    Object* GetConst(int id){ return consts[id]; }
    const GCVecOP GetOPS(){ return opcode; }
    void PushOP(OP op) { opcode.push_back(op); }   
    void AddChild(CodeObject* c);
    int GetChildID(CodeObject* c);
    CodeObject* GetChild(int id) { return children[id]; }
};

#endif
