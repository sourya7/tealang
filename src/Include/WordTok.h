#ifndef T_WORD_H
#define T_WORD_H

#include <string>
#include "Token.h"

using std::string;

class WordTok : public Token {
public:
  string value;
  WordTok(string s, Tags t, ulong l) : Token(t, l), value(s) {}
  WordTok(char c, Tags t, ulong l) : Token(t, l), value(1, c) {}
};

#endif
