#ifndef T_REAL_H
#define T_REAL_H
#include "Token.h"

class RealTok : public Token {
    double number;
public:
    RealTok(double n, uint l) : Token(Tags::REAL,l), number(n) {}
};

#endif
