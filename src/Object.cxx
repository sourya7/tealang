#include <string>
#include <cassert>
#include "Object.h"
#include "Token.h"
#include "RealTok.h"
#include "NumberTok.h"
#include "WordTok.h"

using std::string;

/*
 * 
 */

Object* Object::FromToken(Token* t){
    Object* o;
    switch(t->tag){
        case Tags::NUM:
            o = new Object(static_cast<NumberTok*>(t)->value);
            break;
        case Tags::REAL:
            o = new Object(static_cast<RealTok*>(t)->value);
            break;
        case Tags::STR:
            o = new Object(static_cast<WordTok*>(t)->value.c_str());
            break;
        default:
            assert(false && "This should not happen");
            break;
    }

    return o;
}

