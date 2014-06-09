#ifndef T_WORD_H
#define T_WORD_H

#include <string>
#include "Token.h"

class WordToken : public Token {
  std::string value_;

public:
  std::string getValue() const { return value_; }
  WordToken(std::string str, Tags tag, ulong line)
      : Token(tag, line), value_(str) {}
  WordToken(char ch, Tags tag, ulong line) : Token(tag, line), value_(1, ch) {}
};

#endif
