#ifndef T_VM_H
#define T_VM_H

class CodeObject;
class Frame;

class VM{
private:
    Frame* frame;
public:
    static void ExecCode(CodeObject* co);
};
#endif
