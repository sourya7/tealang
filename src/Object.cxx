#include <string>
#include <cassert>
#include "Object.h"
#include "DoubleObj.h"
#include "StringObj.h"
#include "IntegerObj.h"
#include "Token.h"
#include "RealTok.h"
#include "NumberTok.h"
#include "WordTok.h"

using std::string;

SObject Object::NIL;
SObject Object::FromToken(Token* t){
    SObject o;
    switch(t->tag){
        case Tags::NUM:
            o = make_shared<IntegerObj>(GUARD_CAST<NumberTok*>(t)->value);
            break;
        case Tags::REAL:
            o = make_shared<DoubleObj>(GUARD_CAST<RealTok*>(t)->value);
            break;
        case Tags::STR:
            o = make_shared<StringObj>(GUARD_CAST<WordTok*>(t)->value.c_str());
            break;
        default:
            assert(t->tag != Tags::BCIO);
            assert(t->tag != Tags::BSQO);
            cerr << (int)t->tag << "\n";
            assert(false && "This should not happen");
            break;
    }
    return o;
}

