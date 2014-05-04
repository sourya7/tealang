#ifndef T_OPCODE_H
#define T_OPCODE_H

enum class OPC {
    /* User controlled OPs */
    AND = 200,BAND,OR,BOR,DECR,SUB,INCR,ADD,POWER,MULT,NEQ,
    NOT,LEQ,LSHIFT,LT,GEQ,RSHIFT,GT,DIV,INV,XOR,EQ,MOD,

    /* Internal OP's */
    LOAD_CONSTANT, LOAD_VALUE, STORE_VALUE, JMP_IF, JMP_IF_ELSE,
    CALL, C_CALL
};

class OP {
private:
    int argA, argB;
    bool hasArgA = false;
    bool hasArgB = false;
public:
    OP(OPC o) : opc(o) {}
    OP(OPC o, int a) : opc(o),hasArgA(true),argA(a) {} 
    OP(OPC o, int a, int b) : opc(o),hasArgA(true),hasArgB(true),argA(a),argB(b) {} 
    const OPC  opc;
    bool HasArgA() { return hasArgA; }
    int GetArgA() { return hasArgA ? argA : -1; }

    bool HasArgB() { return hasArgB; }
    int GetArgB() { return hasArgB ? argB : -1; }
};

#endif
