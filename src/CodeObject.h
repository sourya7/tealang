#ifndef T_CODEOBJECT_H
#define T_CODEOBJECT_H

#include <string>
#include "TObject.h"
#include "OPCode.h"

class CodeObject{
private:
    vector<string> names;
    vector<TObject*> consts;
    vector<OP> opcode;
};

#endif
