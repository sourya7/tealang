#include <string>
#include "Object.h"
#include "Objects/DoubleObject.h"
#include "Objects/StringObject.h"
#include "Objects/IntegerObject.h"
#include "Objects/BooleanObject.h"
#include "Token.h"
#include "RealToken.h"
#include "NumberToken.h"
#include "WordToken.h"
#include "CodeObject.h"

SObject Object::NIL;
SObject Object::fromToken(Token *t) {
  SObject o;
  switch (t->getTag()) {
  case Tags::NUM:
    o = std::make_shared<IntegerObject>(
        GUARD_CAST<NumberToken *>(t)->getValue());
    break;
  case Tags::REAL:
    o = std::make_shared<DoubleObject>(GUARD_CAST<RealToken *>(t)->getValue());
    break;
  case Tags::STR:
    o = std::make_shared<StringObject>(GUARD_CAST<WordToken *>(t)->getValue());
    break;
  default:
    assert(false && "This should not happen");
    break;
  }
  return o;
}

SObject Object::operator&&(const SObject &rhs) {
  if (isTrue() && rhs->isTrue()) {
    return BooleanObject::TRUE;
  }
  return BooleanObject::FALSE;
}

SObject Object::operator||(const SObject &rhs) {
  if (isTrue() || rhs->isTrue()) {
    return BooleanObject::TRUE;
  }
  return BooleanObject::FALSE;
}
