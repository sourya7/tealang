#ifndef T_VM_H
#define T_VM_H
#include <stack>
#include "GC.h"
using std::stack;
class CFunction;

class CodeObject;
class Frame;
class Object;

class VM : public TGC {
private:
    static stack<Object*> vmStack;
    static void Push(Object* a) { vmStack.push(a); }
    static Object* Pop() { 
        Object* top = vmStack.top(); 
        vmStack.pop(); 
        return top; 
    }
public:
    static void ExecCode(CodeObject*);
    friend class CFunction;
};
#endif
