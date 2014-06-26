#ifndef T_OPCODE_H
#define T_OPCODE_H

enum class Opc {
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
  UNARY_ADD,
  UNARY_SUB,
  DOT,

  /* Internal OP's */
  LOAD_CONSTANT,
  LOAD_VALUE,
  STORE_VALUE,
  JMP_IF,
  JMP_IF_ELSE,
  CALL,
  C_CALL,
  RETURN,
  BREAK,
  CONTINUE,
  WHILE,
  CALL_METHOD,
  INIT_INSTANCE
};

class Op {
private:
  int argA_, argB_;
  std::string str_;
  bool hasArgA_ = false;
  bool hasArgB_ = false;
  bool hasStr_ = false;

public:
  const Opc opc_;
  Op(Opc opc) : opc_(opc) {}
  Op(Opc opc, int a) : argA_(a), hasArgA_(true), opc_(opc) {}
  Op(Opc opc, int a, int b)
      : argA_(a), argB_(b), hasArgA_(true), hasArgB_(true), opc_(opc) {}
  Op(Opc opc, std::string str) : str_(str), hasStr_(true), opc_(opc) {}
  bool hasArgA() { return hasArgA_; }
  bool hasStr() { return hasStr_; }
  int getArgA() { return hasArgA_ ? argA_ : -1; }

  bool hasArgB() { return hasArgB_; }
  int getArgB() { return hasArgB_ ? argB_ : -1; }
  std::string getStr() { return hasStr_ ? str_ : "NIL"; }
};

#endif
