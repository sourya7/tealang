#ifndef T_OPTOK_H
#define T_OPTOK_H
#include "Token.h"
#include "OPCode.h"

class OPTok : public Token {
public:
    OP value;
    OPTok(OP op, ulong l) : Token(Tags::OP,l), value(op) {}
};
#endif
