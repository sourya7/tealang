#ifndef T_NUMBER_H
#define T_NUMBER_H
#include "ltoken.h"
class Number : public Token {
public:
    int number;
    Number(int n, ulong l) : Token(Tags::NUM,l), number(n) {}
};
#endif
