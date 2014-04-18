#ifndef T_LEXER_H
#define T_LEXER_H

#include <string>
#include <istream>
#include <map>
#include "ltoken.h"
#include "lword.h"

#define IFMATCHELSE(match, ifMatch, elseMatch) \
    if(ReadAndMatch(match)){ return new Token(ifMatch, line); } \
    else{ return new Token(elseMatch, line); }

#define IFMATCHELIFELSE(match, ifMatch, matchElif, elifMatch, elseMatch) \
    if(ReadAndMatch(match)){ return new Token(ifMatch, line); } \
    else if(peek == matchElif) { return new Token(elifMatch, line); } \
    else{ return new Token(elseMatch, line); }


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
