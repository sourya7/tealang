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
    void reserve(Word w);
    istream* inputStream;

    Token getNumericToken();
    Token getIdentifierToken();
    int decFromHex(string hexStr);
    int decFromOct(string octStr);
    int decFromBin(string binStr);
    int decFromDec(string decStr);
    double floatFromFloat(string floatStr);

public: 
    void printAll();
    Lexer(istream pistream);
    void readChar();
    bool readAndMatch(char ch);
    Token scan();
};

#endif
