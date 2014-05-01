#ifndef T_OPCODE_H
#define T_OPCODE_H

enum class OP {
    /* User controlled OPs */
    AND = 200,BAND,OR,BOR,DECR,SUB,INCR,ADD,POWER,MULT,NEQ,
    NOT,LEQ,LSHIFT,LT,GEQ,RSHIFT,GT,DIV,INV,XOR,EQ,MOD,

    /* Internal OP's */
    LOAD_CONSTANT, LOAD_VALUE
};

#endif
