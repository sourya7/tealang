#ifndef T_VM_H
#define T_VM_H
#include "GC.h"
class CFunction;

class CodeObject;
class Frame;
class Object;

class VM : public TGC {
private:
    static VecSObj vmStack;
    static VecSCodeObj coStack;
    static VecPairVecOPInt opsStack;

    static SInt opid;  //currentopid
    static SVecOP ops; //currentOps
    static SCodeObj co; //currentCo

    static void Push(SObject a);
    static SObject Pop();
    static bool RetFlag;
    static void ResetFlags() {
        RetFlag = false;
    }
    static void PopCO();
    static void PushCO(SCodeObj c);
public:
    static void ExecCode(SCodeObj c);
    friend class CFunction;
};
#endif
