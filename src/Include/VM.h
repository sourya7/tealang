#ifndef T_VM_H
#define T_VM_H
#include "GC.h"
class CFunction;

class CodeObject;
class Frame;
class Object;

class VM : public TGC {
private:
    static GCStackObjPtr vmStack;
    static void Push(Object* a) { vmStack.push_back(a); }
    static Object* Pop() { 
        Object* top = vmStack.back(); 
        vmStack.pop_back(); 
        return top; 
    }
    static bool RetFlag;
    static void ResetFlags() {
        RetFlag = false;
    }
public:
    static void ExecCode(CodeObject*);
    friend class CFunction;
};
#endif
