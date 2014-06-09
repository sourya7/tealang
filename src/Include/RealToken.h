#ifndef T_REAL_H
#define T_REAL_H
#include "Token.h"

class RealToken : public Token {
  double value_;

public:
  double getValue() const { return value_; }
  RealToken(double value, uint line) : Token(Tags::REAL, line), value_(value) {}
};

#endif
