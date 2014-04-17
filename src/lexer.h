#ifndef T_LEXER_H
#define T_LEXER_H

#include <string>
#include <istream>
#include <map>
#include "ltoken.h"
#include "lword.h"

#define IFMATCHELSE(match, ifMatch, elseMatch) \
    if(ReadAndMatch(match)){ return new Token(ifMatch); } \
    else{ return new Token(elseMatch); }

#define IFMATCHELIFELSE(match, ifMatch, matchElif, elifMatch, elseMatch) \
    if(ReadAndMatch(match)){ return new Token(ifMatch); } \
    else if(peek == matchElif) { return new Token(elifMatch); } \
    else{ return new Token(elseMatch); }


using std::string;
using std::istream;

typedef std::map<string, Token> IDTable;

class Lexer {
private:
    char peek;
    unsigned int line;
    IDTable words;
    istream* inputStream;
    Token* currentTok;

    void Reserve(Word w);
    Token* ParseNumericToken();
    Token* ParseIdentifierToken();
    Token* ParseSpecialNumber();
    void ReadChar();
    bool ReadAndMatch(char ch);
    Token* ParseStringLiteral();
    Token* Scan();
public: 
    Token* Next();
    Token* GetCurrent() { return currentTok; };
    Lexer(istream* pistream);
};


#endif
