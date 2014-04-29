#include <string>
#include <cassert>
#include "TObject.h"
#include "Token.h"
#include "RealTok.h"
#include "NumberTok.h"
#include "WordTok.h"

using std::string;

/*
 * 
 */


static TObject* FromToken(Token* t){
    TObject* o;
    switch(t->tag){
        case Tags::NUM:
            o = new TObject(static_cast<NumberTok*>(t)->value);
            break;
        case Tags::REAL:
            o = new TObject(static_cast<RealTok*>(t)->value);
            break;
        case Tags::STR:
            o = new TObject(static_cast<WordTok*>(t)->value.c_str());
            break;
        default:
            assert(false && "This should not happen");
            break;
    }

    return o;
}

