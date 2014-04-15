#ifndef T_REAL_H
#define T_REAL_H
#include "token.h"
class Real : public Token {
    double number;
public:
    Real(double pnumber, Tags ptag) : Token(ptag), number(pnumber) {}
};
#endif
