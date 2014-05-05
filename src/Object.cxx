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

Object* Object::NIL;
Object* Object::FromToken(Token* t){
    Object* o;
    switch(t->tag){
        case Tags::NUM:
            o = new IntegerObj(GUARD_CAST<NumberTok*>(t)->value);
            break;
        case Tags::REAL:
            o = new DoubleObj(GUARD_CAST<RealTok*>(t)->value);
            break;
        case Tags::STR:
            o = new StringObj(GUARD_CAST<WordTok*>(t)->value.c_str());
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

