#include <string>
#include <istream>
#include <iostream>
#include <algorithm>
#include <map>
#include <cassert>
#include "Token.h"
#include "WordTok.h"
#include "NumberTok.h"
#include "RealTok.h"
#include "OPTok.h"
#include "OPCode.h"
#include "Lexer.h"

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
        return new WordTok(tmp, Tags::ID, line);

        /* TODO use these instead
        if(isHex) return new NumberTok(decFromHex(tmp), line);
        else if(isHex) return new NumberTok(decFromOct(tmp), line);
        else return new NumberTok(decFromBin(tmp), line);
        */
    }
    return new NumberTok(0, line);
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
    if(peek != '.') return new WordTok(tmp, Tags::ID, line); ////return new NumberTok(decFromDec(tmp), line);

    //handle real numbers
    do{
        tmp += peek;
        ReadChar();
    }while(isdigit(peek));
    return new WordTok(tmp, Tags::ID, line); //RealTok(floatFromFloat(tmp), line);
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

    return new WordTok(tmp, tag, line);
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

#define IFMATCHELSE(ifMatch,ifTok,elseTok) \
    if(ReadAndMatch(ifMatch)){return new OPTok(ifTok,line);} \
    else{return new OPTok(elseTok,line);}

#define IFMATCH2ELSE(ifMatch,ifTok,elifMatch,elifTok,elseTok) \
    if(ReadAndMatch(ifMatch)){return new OPTok(ifTok, line);} \
    else if(peek == elifMatch){return new OPTok(elifTok, line);}\
    else{return new OPTok(elseTok, line); }

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
        case '&': { IFMATCHELSE('&', OP::AND, OP::BAND); } 
        case '|': { IFMATCHELSE('|', OP::OR, OP::BOR); } 
        case '-': { IFMATCHELSE('-', OP::DECR, OP::SUB); }
        case '+': { IFMATCHELSE('+', OP::INCR, OP::ADD); }
        case '*': { IFMATCHELSE('*', OP::POWER, OP::MULT); }
        case '!': { IFMATCHELSE('=', OP::NEQ, OP::NOT); }
        case '<': { IFMATCH2ELSE('=', OP::LEQ, '<', OP::LSHIFT, OP::LT); }
        case '>': { IFMATCH2ELSE('=', OP::GEQ, '>', OP::RSHIFT, OP::GT); }
        case '/': { ReadChar(); return new OPTok(OP::DIV, line); }
        case '%': { ReadChar(); return new OPTok(OP::MOD, line); }
        case '~': { ReadChar(); return new OPTok(OP::INV, line);  }
        case '^': { ReadChar(); return new OPTok(OP::XOR, line); }
        case '[': { ReadChar(); return new Token(Tags::BSQO, line);   }
        case ']': { ReadChar(); return new Token(Tags::BSQC, line);   }
        case '(': { ReadChar(); return new Token(Tags::BCIO, line);   }
        case ')': { ReadChar(); return new Token(Tags::BCIC, line);   }
        case '{': { ReadChar(); return new Token(Tags::BCUO, line);   }
        case '}': { ReadChar(); return new Token(Tags::BCUC, line);   }
        case '"': case '\'': { return ParseStringLiteral(); } 
        case -1: { return new Token(Tags::SEOF, line); }
        case '=': { if(ReadAndMatch('=')) return new OPTok(OP::EQ, line);
                    else return new WordTok('=', Tags::ASSIGN, line); }
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
    return new WordTok(tmp, Tags::STR, line);
}
