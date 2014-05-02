#ifndef T_IRBUILDER_H
#define T_IRBUILDER_H

class CodeObject;
class Token;

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
class IRBuilder {
private:
    CodeObject* co = nullptr;
public:
    IRBuilder();
    IRBuilder(IRBuilder* parent);

    uint GetOPSize(Token* t);
    void PerformOP(Token* t);
    void PushValue(Token* t);
    void StoreValue(Token* t);
    void DeclVar(Token* t);
    void CondJump(IRBuilder* ifBlk);
    void CondJump(IRBuilder* ifBlk, IRBuilder* elBlk);
    //TODO For debug
    void DumpCodeObject();
    CodeObject* GetCodeObject();
};

#endif
