#ifndef T_OPCODE_H
#define T_OPCODE_H

enum class OPC {
    /* User controlled OPs */
    AND = 200,BAND,OR,BOR,DECR,SUB,INCR,ADD,POWER,MULT,NEQ,
    NOT,LEQ,LSHIFT,LT,GEQ,RSHIFT,GT,DIV,INV,XOR,EQ,MOD,

    /* Internal OP's */
    LOAD_CONSTANT, LOAD_VALUE
};

class OP {
private:
    int arg;
    bool hasArg = false;
public:
    OP(OPC o) : opc(o) {}
    OP(OPC o, int a) : opc(o), hasArg(true), arg(a) {} 
    const OPC  opc;
    bool HasArg() { return hasArg; }
    int GetArg() { return hasArg ? arg : -1; }
};

#endif
