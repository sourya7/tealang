#ifndef T_CODEOBJECT_H
#define T_CODEOBJECT_H

#include <string>
#include "GC.h"
#include "Debug.h"
#include "Object.h"
#include "OPCode.h"

using std::string;
class CodeObject;
typedef GV<Object*>::Vector GCVecObjPtr;
typedef GV<string>::Vector GCVecString;
typedef GV<OP>::Vector GCVecOP;
typedef GV<CodeObject*>::Vector GCVecCodeObjPtr;

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
    int GetID(string var);
    int PushID(string var); 
    int PushConst(Object* o);
    void StoreIDVal(int id, Object* val);

    Object* GetIDVal(int id){ return vals[id]; } 
    Object* GetConst(int id){ return consts[id]; }
    const GCVecOP GetOPS(){ return opcode; }
    void PushOP(OP op) { opcode.push_back(op); }   
    void AddChild(CodeObject* c);
    int GetChildID(CodeObject* c);
    CodeObject* GetChild(int id) { return children[id]; }
};

#endif
