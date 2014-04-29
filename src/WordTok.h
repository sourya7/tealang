#ifndef T_WORD_H
#define T_WORD_H

#include <string>
#include "Token.h"

using std::string;

class WordTok : public Token {
public:
    const string lexeme;
    WordTok(string s, Tags t, ulong l) : Token(t,l), lexeme(s) {}
    WordTok(char c, Tags t, ulong l) : Token(t, l), lexeme(1, c) {}
};

#endif
