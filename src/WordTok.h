#ifndef T_WORD_H
#define T_WORD_H

#include "ltoken.h"
#include <string>

using std::string;

class Word : public Token {
public:
    const string lexeme;
    Word(string s, Tags t, ulong l) : Token(t,l), lexeme(s) {}
    Word(char c, Tags t, ulong l) : Token(t, l), lexeme(1, c) {}
};

#endif
