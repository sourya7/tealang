#include <string>
#include <cassert>
#include "Object.h"
#include "Token.h"
#include "RealTok.h"
#include "NumberTok.h"
#include "WordTok.h"

using std::string;

#define PERFORM_NUM_OP(op)\
if(IsNumeral() && rhs.IsNumeral()){\
    bool isBothDbl = IsDouble() && rhs.IsDouble();\
    if(isBothDbl) return new Object(value->d op rhs.value->d);\
    else if(IsDouble()) return new Object(value->d op rhs.value->i);\
    else if(rhs.IsDouble()) return new Object(value->i op rhs.value->d);\
    else return new Object(value->i op rhs.value->i);\
}\
else{\
    assert(false && "Not implemented!");\
    return nullptr;\
}\


/*
 * TODO
 * Refactor these code to reduce code duplication
 */

Object* Object::operator+(Object rhs){
    PERFORM_NUM_OP(+)
}

Object* Object::operator*(Object rhs){
    PERFORM_NUM_OP(*)
}

Object* Object::operator-(Object rhs){
    PERFORM_NUM_OP(-)
}

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

