#ifndef T_REAL_H
#define T_REAL_H
#include "ltoken.h"
class Real : public Token {
    double number;
public:
    Real(double n, uint l) : Token(Tags::REAL,l), number(n) {}
};
#endif
