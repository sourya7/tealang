#ifndef T_OPTOK_H
#define T_OPTOK_H
#include "Token.h"
#include "OpCode.h"

class OpToken : public Token {
  Opc value_;

public:
  Opc getValue() const { return value_; }
  OpToken(Opc opc, ulong line) : Token(Tags::OP, line), value_(opc) {}
};
#endif
