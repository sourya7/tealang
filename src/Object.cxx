#include <string>
#include "Object.h"
#include "DoubleObj.h"
#include "StringObj.h"
#include "IntegerObj.h"
#include "Token.h"
#include "RealTok.h"
#include "NumberTok.h"
#include "WordTok.h"
#include "CodeObject.h"

using std::string;

SObject Object::NIL;
SObject Object::FromToken(Token* t){
    SObject o;
    switch(t->tag){
        case Tags::NUM:
            o = MakeShared<IntegerObj>(GUARD_CAST<NumberTok*>(t)->value);
            break;
        case Tags::REAL:
            o = MakeShared<DoubleObj>(GUARD_CAST<RealTok*>(t)->value);
            break;
        case Tags::STR:
            o = MakeShared<StringObj>(GUARD_CAST<WordTok*>(t)->value);
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

