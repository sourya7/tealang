#ifndef T_CODEOBJECT_H
#define T_CODEOBJECT_H

#include <string>
#include <vector>
#include "Object.h"
#include "OPCode.h"

using std::vector;
using std::string;

class CodeObject{
private:
    //variables in the codeobject scope
    vector<string> ids;
    //constants in the codeobject scope
    vector<Object*> consts;
    //opcodes for this codeobject
    vector<OP> opcode;

public:
    void PushOP(OP op, int val) { }   
    size_t PushConst(Object* o) {
        consts.push_back(o);
        return consts.size() - 1;
    }
    size_t PushID(string id) {
        ids.push_back(id);
        return ids.size() - 1;
    } 
};

#endif
