#ifndef T_VM_H
#define T_VM_H
#include "Common.h"
class CFunction;

class Vm {
private:
  static VecSObject vmStack_;
  static VecSCodeObject coStack_;
  static VecPairSVecOpSInt opsStack_;

  static SInt opId_;              // currentopid
  static SVecOp vecOp_;           // currentOps
  static SCodeObject codeObject_; // currentCo

  static void popCodeObject();
  static void pushCodeObject(const SCodeObject &c);
  static void callFunc(const SObject &fnob);
  static void callMethod(const SObject &instance, const SObject &funcName);
  static void callModule(const SObject &instance, const SObject &funcName);
  static void getMethodProp(const SObject &instance, const SObject &propName);
  static void execCode(const SCodeObject &c);

public:
  static void execMain(const SCodeObject &c, int argc, char *args[]);
};
#endif
