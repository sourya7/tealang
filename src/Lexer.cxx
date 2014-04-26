#include <string>
#include <istream>
#include <iostream>
#include <algorithm>
#include <map>
#include <cassert>
#include "ltoken.h"
#include "lword.h"
#include "lnumber.h"
#include "lreal.h"
#include "lexer.h"

using namespace std;

/* debug stuff */
#define LEN_BLOCKTOKENS 6
string blockTokens[] = {"defclass", "defun", "if", "for", "try", "while"};

#define LEN_FLWBLKTOKENS 3
string flwBlkTokens[] = {"elif", "catch", "else"};

#define LEN_ENDTOKENS 6
string endTokens[] = {"endif","endfor","endtry","endwhile","endclass","endfun"};

#define LEN_CMDTOKENS 5
string cmdTokens [] = {"in", "var", "isa", "return", "break"};

/* 
* Some helper functions for converting from numeric string types   
* TODO
*/
int decFromHex(string hexStr){
    return 0;
}

//TODO
int decFromOct(string octStr){
    return 0;
}

//TODO
int decFromBin(string binStr){
    return 0;
}

//TODO
int decFromDec(string decStr){
    return 0;
}

//TODO
double floatFromFloat(string floatStr){
    return 0;
}

Token* Lexer::ParseSpecialNumber(){
    bool isHex = peek == 'x';
    bool isOctal = isdigit(peek);
    bool isBinary = peek == 'b';
    if(isHex || isBinary) ReadChar();
    if(isHex || isOctal || isBinary){
        string tmp;
        do {
            tmp += peek;
            ReadChar();
        } while((isHex && isxdigit(peek))  || 
                (isOctal && isdigit(peek)) || 
                (isBinary && (peek == '0' || peek == '1')));
        return new Word(tmp, Tags::ID, line);

        /* TODO use these instead
        if(isHex) return new Number(decFromHex(tmp), line);
        else if(isHex) return new Number(decFromOct(tmp), line);
        else return new Number(decFromBin(tmp), line);
        */
    }
    return new Number(0, line);
}

Token* Lexer::ParseNumericToken(){
    if(peek == '0'){
        ReadChar();
        return ParseSpecialNumber();
    }

    //handle decimal numbers
    string tmp;
    do{
        tmp += peek;
        ReadChar();
    }while(isdigit(peek));
    if(peek != '.') return new Word(tmp, Tags::ID, line); ////return new Number(decFromDec(tmp), line);

    //handle real numbers
    do{
        tmp += peek;
        ReadChar();
    }while(isdigit(peek));
    return new Word(tmp, Tags::ID, line); //Real(floatFromFloat(tmp), line);
}

Token* Lexer::ParseIdentifierToken(){
    string tmp;
    while(isalpha(peek) || isdigit(peek)){
        tmp += peek;  
        ReadChar();
    }
    Tags tag;
    if(peek == ':') { ReadChar(); tmp += ':'; tag = Tags::PARAM; }
    else if(count(blockTokens, blockTokens + LEN_BLOCKTOKENS, tmp) > 0)
        tag = Tags::BLK;
    else if(count(flwBlkTokens, flwBlkTokens + LEN_FLWBLKTOKENS, tmp) > 0)
        tag = Tags::FLWBLK;
    else if(count(endTokens, endTokens + LEN_ENDTOKENS, tmp) > 0)
        tag = Tags::ENDBLK;
    else if(count(cmdTokens, cmdTokens + LEN_CMDTOKENS, tmp) > 0)
        tag = Tags::CMD;
    else
        tag = Tags::ID;

    return new Word(tmp, tag, line);
}

Lexer::Lexer(istream* i){ 
    inputStream = i; 
    peek = ' '; 
}

void Lexer::ReadChar(){ 
    bool res = inputStream->get(peek); 
    if(!res || inputStream->eof()) peek = -1;
}

bool Lexer::ReadAndMatch(char ch){ 
    ReadChar();
    if(peek != ch){ return false; }
    peek = ' ';
    return true;
} 

#define IFMATCHELSE(ifMatch, elseMatch) \
    if(!ReadAndMatch(ifMatch)){ return new Word(ifMatch, Tags::OP, line); } \
    else{ return new Word(elseMatch, Tags::OP, line); }

#define IFMATCHELIFELSE(ifMatch, elifMatch, elseMatch) \
    if(ReadAndMatch(match)){ return new Word(match, Tags::OP, line); } \
    else if(peek == elifMatch) { return new Token(elifMatch, Tags::OP, line); } \
    else{ return new Token(elseMatch, Tags::OP, line); }

#define IFMATCH2ELSE(match, fmatch) \
  ReadChar(); string ret(1,match); \
  if(peek == fmatch || peek == match) ret += peek; \
  return new Word(ret, Tags::OP, line);

/*
 * TODO - Handle comments
 * TODO - Use a symbol table to store the identifiers, strings, and numbers
 *
 */
Token* Lexer::Scan(){
    //Get rid of the white space
    for(;;ReadChar()){
        if(peek == '\n') { line += 1; } //
        else if(isspace(peek)){ continue; }
        else { break; }
    }
    assert(peek != 10);

    switch(peek){
        case '&': { IFMATCHELSE('&', "&&"); }
        case '|': { IFMATCHELSE('|', "||"); }
        case '-': { IFMATCHELSE('-', "--"); }
        case '+': { IFMATCHELSE('+', "++"); }
        case '*': { IFMATCHELSE('*', "**"); }
        case '!': { IFMATCHELSE('=', "!="); }
        case '<': { IFMATCH2ELSE('=', '<'); }
        case '>': { IFMATCH2ELSE('=', '>'); }
        case '/': { ReadChar(); return new Word('/', Tags::OP, line); }
        case '~': { ReadChar(); return new Word('~', Tags::OP,line);  }
        case '^': { ReadChar(); return new Word('^', Tags::OP, line); }
        case '[': { ReadChar(); return new Token(Tags::BSQO, line);   }
        case ']': { ReadChar(); return new Token(Tags::BSQC, line);   }
        case '(': { ReadChar(); return new Token(Tags::BCIO, line);   }
        case ')': { ReadChar(); return new Token(Tags::BCIC, line);   }
        case '{': { ReadChar(); return new Token(Tags::BCUO, line);   }
        case '}': { ReadChar(); return new Token(Tags::BCUC, line);   }
        case '"': case '\'': { return ParseStringLiteral(); } 
        case -1: { return new Token(Tags::SEOF, line); }
        case '=': { if(ReadAndMatch('=')) return new Word("==", Tags::OP, line);
                    else return new Word('=', Tags::ASSIGN, line); }
        default: {
            return isdigit(peek) ? ParseNumericToken() : ParseIdentifierToken(); }
    }
}

/*
 * TODO - Handle Multi line strings
 * TODO - Handle Escape Characters
 *
 * As for the escape characters, only the double quote or the multi line quote
 * can represent them. Using the single quote, the escape characters are not 
 * interpreted as special characters. 
 */
Token* Lexer::ParseStringLiteral(){
    string tmp;
    char quote = peek;
    ReadChar();
    do{
        tmp += peek;
    } while(!ReadAndMatch(quote));
    return new Word(tmp, Tags::STR, line);
}

