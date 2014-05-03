#ifndef T_VM_H
#define T_VM_H
#include <stack>
#include "GC.h"
using std::stack;

class CodeObject;
class Frame;
class Object;

class VM : public TGC {
private:
    stack<Object*> nstack;
    void Push(Object* a) { nstack.push(a); }
    Object* Pop() { Object* top = nstack.top(); nstack.pop(); return top; }
public:
    static void ExecCode(CodeObject*);
};
#endif
