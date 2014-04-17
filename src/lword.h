#ifndef T_WORD_H
#define T_WORD_H

#include "token.h"
#include <string>

using std::string;

class Word : public Token {
public:
    const string lexeme;
    Word(string plexeme, Tags ptag) : Token(ptag), lexeme(plexeme) {}
};

#endif
