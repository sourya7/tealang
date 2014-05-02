#ifndef T_OPTOK_H
#define T_OPTOK_H
#include "Token.h"
#include "OPCode.h"

class OPTok : public Token {
public:
    OPC value;
    OPTok(OPC op, ulong l) : Token(Tags::OP,l), value(op) {}
};
#endif
