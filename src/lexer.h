#ifndef T_LEXER_H
#define T_LEXER_H

#include <string>
#include <istream>
#include <map>
#include "ltoken.h"
#include "lword.h"

using std::string;
using std::istream;

typedef std::map<string, Token> IDTable;

class Lexer {
private:
    char peek;
    unsigned long line;
    IDTable words;
    istream* inputStream;

    void Reserve(Word w);
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
