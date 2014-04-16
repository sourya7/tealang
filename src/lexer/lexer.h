#ifndef T_LEXER_H
#define T_LEXER_H

#include <string>
#include <istream>
#include <map>
#include "token.h"
#include "word.h"

using std::string;
using std::istream;

typedef std::map<string, Token> IDTable;

class Lexer {
private:
    char peek;
    IDTable words;
    istream* inputStream;

    void reserve(Word w);
    Token getNumericToken();
    Token getIdentifierToken();
    Token parseSpecialNumber();
    Token parseStringLiteral();
    int debugCounter = 0;
public: 
    void printAll();
    void readChar();
    bool readAndMatch(char ch);
    Token scan();
    Lexer(istream& pistream);
};

#endif
