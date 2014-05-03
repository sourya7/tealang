#ifndef T_LEXER_H
#define T_LEXER_H

#include "GC.h"
#include <string>
#include <istream>
#include "Token.h"
#include "WordTok.h"

using std::string;
using std::istream;

class Lexer : public TGC {
private:
    char peek;
    unsigned long line;
    istream* inputStream;

    void Reserve(WordTok w);
    Token* ParseNumericToken();
    Token* ParseIdentifierToken();
    Token* ParseSpecialNumber();
    void ReadChar();
    bool ReadAndMatch(char ch);
    Token* ParseStringLiteral();
public: 
    Token* Scan();
    Lexer(istream* pistream);
};


#endif
