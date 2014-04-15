#ifndef T_NUMBER_H
#define T_NUMBER_H
#include "token.h"
class Number : public Token {
    int number;
public:
    Number(int pnumber, Tags ptag) : Token(ptag), number(pnumber) {}
};
#endif
