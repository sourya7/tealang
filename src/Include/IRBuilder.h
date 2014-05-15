#ifndef T_IRBUILDER_H
#define T_IRBUILDER_H

#include "GC.h"
#include "OPCode.h"
#include <string>
class CodeObject;
class Object;
using std::string;
/*
 * IRBuilder (IRCompiler?) is a helper function that helps compile the AST
 * into bytecode. It is responsible for creating the frames and codeobjects
 *
 * DESIGN: There is only going to be one instance of this class for now and so it 
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
class IRBuilder : public TGC {
private:
    SCodeObj co;
public:
    IRBuilder();
    IRBuilder(SIRBuilder parent);

    void PerformOP(OPC v);
    void StoreValue(string v);
    void LoadValue(string v);
    void LoadConst(SObject o);
    void DeclVar(string v);
    void DeclVar(string v, SObject o);
    void CallMethod(string object, string method);
    void DeclFunc(string n, int ac, SIRBuilder f); 
    void DeclClass(string n, SIRBuilder b);
    void DeclCFunc(string n, int ac); 
    void DeclWhile(SIRBuilder expr, SIRBuilder body);
    void CondJump(SIRBuilder ifBlk);
    void CondJump(SIRBuilder ifBlk, SIRBuilder elBlk);
    void CallFunc(string fn);
    void Return(bool hasArg = false);
    void ReturnArg(){ Return(true); }
    SCodeObj GetCodeObject();
};

#endif
