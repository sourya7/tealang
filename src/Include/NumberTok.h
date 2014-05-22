#ifndef T_NUMBER_H
#define T_NUMBER_H
#include "Token.h"
class NumberTok : public Token {
public:
  long value;
  NumberTok(int n, ulong l) : Token(Tags::NUM, l), value(n) {}
};
#endif
