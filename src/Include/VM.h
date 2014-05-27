#ifndef T_VM_H
#define T_VM_H
#include "GC.h"
class CFunction;
class CodeObject;
class Frame;
class Object;

class VM {
private:
  static VecSObj vmStack;
  static VecSCodeObj coStack;
  static VecPairVecOPInt opsStack;

  static SInt opid;   // currentopid
  static SVecOP ops;  // currentOps
  static SCodeObj co; // currentCo

  static void PopCO();
  static void PushCO(const SCodeObj &c);
  static void CallFunc(const SObject &fnob);
  static void CallMethod(const SObject &instance, const SObject &funcName);
  static void CallModule(const SObject &instance, const SObject &funcName);

public:
  static void ExecCode(const SCodeObj &c);
};
#endif
