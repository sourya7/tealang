#ifndef T_CODEOBJECT_H
#define T_CODEOBJECT_H

#include <string>
#include <vector>
#include "Debug.h"
#include "Object.h"
#include "OPCode.h"

using std::vector;
using std::string;

class CodeObject{
private:
    //variables in the codeobject scope
    vector<string> ids;
    //value for those vars
    vector<Object*> vals;
    //constants in the codeobject scope
    vector<Object*> consts;
    //opcodes for this codeobject
    vector<OP> opcode;

public:
    int GetID(string var);
    int PushID(string var); 
    int PushConst(Object* o);
    void StoreIDVal(int id, Object* val);

    Object* GetIDVal(int id){ return vals[id]; } 
    Object* GetConst(int id){ return consts[id]; }
    const vector<OP> GetOPS(){ return opcode; }
    void PushOP(OP op) { opcode.push_back(op); }   
};

#endif
