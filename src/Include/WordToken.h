#ifndef T_WORD_H
#define T_WORD_H

#include <string>
#include "Token.h"

class WordToken : public Token {
public:
  std::string value_;
  WordToken(std::string str, Tags tag, ulong line)
      : Token(tag, line), value_(str) {}
  WordToken(char ch, Tags tag, ulong line) : Token(tag, line), value_(1, ch) {}
};

#endif
