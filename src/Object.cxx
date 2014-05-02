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

/*
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


//
// TODO
// Refactor these code to reduce code duplication
//

Object* Object::operator+(Object rhs){
    bool isNumeral = IsNumeral() && rhs.IsNumeral();
    if(isNumeral) {
        bool isDouble = IsDouble() || rhs.IsDouble();
        if(isDouble) return new Object(GetDouble() + rhs.GetDouble());
    }
    PERFORM_NUM_OP(+)
}

Object* Object::operator*(Object rhs){
    PERFORM_NUM_OP(*)
}

Object* Object::operator-(Object rhs){
    PERFORM_NUM_OP(-)
}

*/
Object* Object::NIL;
Object* Object::FromToken(Token* t){
    Object* o;
    switch(t->tag){
        case Tags::NUM:
            o = new IntegerObj(static_cast<NumberTok*>(t)->value);
            break;
        case Tags::REAL:
            o = new DoubleObj(static_cast<RealTok*>(t)->value);
            break;
        case Tags::STR:
            o = new StringObj(static_cast<WordTok*>(t)->value.c_str());
            break;
        default:
            assert(false && "This should not happen");
            break;
    }

    return o;
}

