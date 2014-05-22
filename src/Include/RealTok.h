#ifndef T_REAL_H
#define T_REAL_H
#include "Token.h"

class RealTok : public Token {
public:
  double value;
  RealTok(double n, uint l) : Token(Tags::REAL, l), value(n) {}
};

#endif
