#ifndef T_IRBUILDER_H
#define T_IRBUILDER_H

#include <string>
#include "OpCode.h"
#include "Common.h"
/*
 * IRBuilder (IRCompiler?) is a helper function that helps compile the AST
 * into bytecode. It is responsible for creating the frames and codeobjects
 *
 * DESIGN: There is only going to be one instance of this class for now and so
 *it
 * is a singleton
 *
 * Basic Thoughts ->
 *      If the AST is a block stucturre, create a new frame for it
 *          - When IRBuilder is first constructed, we create the first frame
 *      The frame contains a codeobject associated with it along with the the
 *      variables it has access to
 *      Each frame has a parent frame that it has access to view
 *
 */
class IrBuilder {
private:
  SCodeObject codeObject_;
  static SIrBuilder globalIrBuilder_;

public:
  IrBuilder();
  IrBuilder(SIrBuilder parent);

  void performOp(Opc v);
  void storeValue(std::string v);
  void loadValue(std::string v);
  void loadConst(SObject o);
  void declVar(std::string v);
  void declVar(std::string v, SObject o);
  void callMethod(std::string method);
  void declFunc(bool i, std::string n, int ac, SIrBuilder f);
  void declClass(std::string n, SIrBuilder b);
  void declCFunc(std::string n, int ac);
  void declWhile(SIrBuilder whileBlk);
  void condJump(SIrBuilder ifBlk);
  void condJump(SIrBuilder ifBlk, SIrBuilder elBlk);
  void callFunc(std::string fn);
  void breakFlow();
  void continueFlow();
  void returnValue(bool hasArg = true);
  void returnNoValue() { returnValue(false); }
  SCodeObject getCodeObject();
  static SIrBuilder getGlobalIrBuilder();
};

#endif
