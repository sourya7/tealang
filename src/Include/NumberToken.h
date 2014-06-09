#ifndef T_NUMBER_H
#define T_NUMBER_H
#include "Token.h"
class NumberToken : public Token {
  long value_;

public:
  long getValue() const { return value_; }
  NumberToken(int value, ulong line) : Token(Tags::NUM, line), value_(value) {}
};
#endif
