#ifndef T_OPCODE_H
#define T_OPCODE_H

enum class OPC {
  /* User controlled OPs */
  AND = 200,
  BAND,
  OR,
  BOR,
  DECR,
  SUB,
  INCR,
  ADD,
  POWER,
  MULT,
  NEQ,
  NOT,
  LEQ,
  LSHIFT,
  LT,
  GEQ,
  RSHIFT,
  GT,
  DIV,
  INV,
  XOR,
  EQ,
  MOD,

  /* Internal OP's */
  LOAD_CONSTANT,
  LOAD_VALUE,
  STORE_VALUE,
  JMP_IF,
  JMP_IF_ELSE,
  CALL,
  C_CALL,
  RETURN,
  WHILE,
  CALL_METHOD,
  INIT_INSTANCE
};

class OP {
private:
  int argA, argB;
  bool hasArgA = false;
  bool hasArgB = false;

public:
  const OPC opc;
  OP(OPC o) : hasArgA(false), hasArgB(false), opc(o) {}
  OP(OPC o, int a) : argA(a), hasArgA(true), opc(o) {}
  OP(OPC o, int a, int b)
      : argA(a), argB(b), hasArgA(true), hasArgB(true), opc(o) {}
  bool HasArgA() { return hasArgA; }
  int GetArgA() { return hasArgA ? argA : -1; }

  bool HasArgB() { return hasArgB; }
  int GetArgB() { return hasArgB ? argB : -1; }
};

#endif
