#ifndef T_NUMBER_H
#define T_NUMBER_H
#include "Token.h"
class NumberTok : public Token {
public:
    int number;
    NumberTok(int n, ulong l) : Token(Tags::NUM,l), number(n) {}
};
#endif
