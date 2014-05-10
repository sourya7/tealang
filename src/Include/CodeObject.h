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
    SVecStr ids;
    //value for those vars
    SVecSObj vals;
    //constants in the codeobject scope
    SVecSObj consts;
    //opcodes for this codeobject
    SVecOP opcode;
    SVecSCodeObj children;
    SCodeObj parent;
    CT type = CT::NORM;
public:
    CodeObject(SCodeObj p) : CodeObject(){
        parent = p;
    }

    CodeObject(const CodeObject& p) {
        parent = p.parent;
        children = p.children;
        opcode = p.opcode;
        consts = p.consts;
        vals = make_shared<VecSObj>(*p.vals);
        ids = p.ids;
        type = p.type;
    }

    CodeObject() {
        ids = make_shared<VecStr>();
        vals = make_shared<VecSObj>();
        consts = make_shared<VecSObj>();
        opcode = make_shared<VecOP>();
        children = make_shared<VecSCodeObj>();
    }

    void SetType(CT t) { type = t; }
    bool IsFunction() { return type == CT::FUNCTION; }
    bool IsMethod() { return type == CT::METHOD; }
    bool IsNorm() { return type == CT::NORM; }
    void SetParent(SCodeObj p) { parent = p; }

    int PushID(string var); 
    int PushConst(SObject o);

    int GetID(string var, int &l);
    int GetID(string var) { int l; return GetID(var, l); } 
    void StoreIDVal(SObject val, int id, int level=0);
    SObject GetIDVal(int id, int level=0);

    SObject GetConst(int id){ return consts->at(id); }
    SVecOP GetOPS(){ return opcode; }
    void PushOP(OP op) { opcode->push_back(op); }   
    void AddChild(SCodeObj c);
    int GetChildID(SCodeObj c);
    SCodeObj GetChild(int id) { return children->at(id); }
};

#endif
