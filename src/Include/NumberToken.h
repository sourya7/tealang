#ifndef T_NUMBER_H
#define T_NUMBER_H
#include "Token.h"
class NumberToken : public Token {
public:
  long value_;
  NumberToken(int value, ulong line) : Token(Tags::NUM, line), value_(value) {}
};
#endif
