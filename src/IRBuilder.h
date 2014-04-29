#ifndef T_IRBUILDER_H
#define T_IRBUILDER_H

class Token;

class IRBuilder {
private:
    IRBuilder() {}
    static IRBuilder* builder;
public:
    static IRBuilder* GetBuilder();
    uint GetOPSize(Token* t);
    void PerformOP(Token* t);
    void PushParams(Token* t);
    void StoreValue(Token* t);
};

#endif
