#ifndef T_VM_H
#define T_VM_H
#include "GC.h"
class CFunction;

class CodeObject;
class Frame;
class Object;

class VM : public TGC {
private:
    static GCVecObjPtr vmStack;
    static GCVecCodeObjPtr coStack;
    static GCVecPairOPIntPtr opsStack;

    static GCVecOP* ops; //currentOps
    static int* opid;  //currentopid
    static CodeObject* co; //currentCo

    static void Push(Object* a);
    static Object* Pop();
    static bool RetFlag;
    static void ResetFlags() {
        RetFlag = false;
    }

    static void PopCO();
    static void PushCO(CodeObject* c);
public:
    static void ExecCode(CodeObject*);
    friend class CFunction;
};
#endif
