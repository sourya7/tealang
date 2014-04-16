#include <string>
#include <istream>
#include <map>
#include "token.h"
#include "word.h"
#include "number.h"
#include "real.h"
#include "lexer.h"

/* 
 * Some helper functions for converting from numeric string types   
 */
//TODO
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

/*
string getStrWhileCond(function<bool(char)>& cond){
    string tmp;
    do{
        readChar();
        tmp += peek;
    }while(cond(peek));
}
*/
/* End of helpers */

Token Lexer::parseSpecialNumber(){
    bool isHex = peek == 'x';
    bool isOctal = peek == isdigit(peek);
    bool isBinary = peek == 'b';
    if(isHex || isOctal || isBinary){
        string tmp;
        do {
            readChar();
            tmp += peek;
        } while((isHex && isxdigit(peek))  || 
                (isOctal && isdigit(peek)) || 
                (isBinary && (peek == 0 || peek == 1)));
        if(isHex) return Number(decFromHex(tmp), Tags::NUM);
        else if(isHex) return Number(decFromOct(tmp), Tags::NUM);
        else return Number(decFromBin(tmp), Tags::NUM);
    }
    return Number(0, Tags::NUM);
}

Token Lexer::getNumericToken(){
    if(peek == 0){
        readChar();
        return parseSpecialNumber();
    }

    //handle decimal numbers
    string tmp;
    do{
        readChar();
        tmp += peek;
    }while(isdigit(peek));
    if(peek != '.') return Number(decFromDec(tmp), Tags::NUM);

    //handle real numbers
    tmp += ".";
    do{
        readChar();
        tmp += peek;
    }while(isdigit(peek));
    return Real(floatFromFloat(tmp), Tags::REAL);
}

Token Lexer::getIdentifierToken(){
    string tmp;
    while(isalpha(peek) || peek == ':' || isdigit(peek)){
        tmp += peek;  
        readChar();
    }
    return Word(tmp, Tags::ID);
}

void Lexer::printAll(){
}

Lexer::Lexer(istream pistream){ 
    inputStream = &pistream; 
    peek = ' '; 
}

void Lexer::readChar(){ 
    *inputStream >> peek; 
}

bool Lexer::readAndMatch(char ch) { 
    readChar();
    if(peek != ch){ return false; }
    peek = ' ';
    return true;
} 

#define IFMATCHELSE(match, ifMatch, elseMatch) \
    if(readAndMatch(match)){ return Token(ifMatch); } \
    else{ return Token(elseMatch); }

#define IFMATCHELIFELSE(match, ifMatch, matchElif, elifMatch, elseMatch) \
    if(readAndMatch(match)){ return Token(ifMatch); } \
    else if(peek == matchElif) { return Token(elifMatch); } \
    else{ return Token(elseMatch); }

Token Lexer::scan(){
    //Get rid of the white space
    for(;;readChar()){
        if(peek == '\n') {} //line += 1;
        else if(!isspace(peek)){ continue; }
        else { break; }
    }
    switch(peek){
        case '&': IFMATCHELSE('&', Tags::AND, Tags::BAND);
        case '|': IFMATCHELSE('|', Tags::OR, Tags::BOR);
        case '-': IFMATCHELSE('-', Tags::DECR, Tags::MINUS);
        case '+': IFMATCHELSE('+', Tags::INCR, Tags::PLUS);
        case '*': IFMATCHELSE('*', Tags::POW, Tags::MULT);
        case '/': return Token(Tags::DIV);
        case '!': IFMATCHELSE('=', Tags::NEQ, Tags::NOT);
        case '~': return Token(Tags::BNOT);
        case '^': return Token(Tags::BXOR);
        case '<': IFMATCHELIFELSE('=', Tags::LTE, '<', Tags::LSHIFT, Tags::LT);
        case '>': IFMATCHELIFELSE('=', Tags::GTE, '>', Tags::RSHIFT, Tags::GT);
        case '=': IFMATCHELSE('=', Tags::EQ, Tags::ASSIGN);
        case '[': return Token(Tags::BSQO);
        case ']': return Token(Tags::BSQC);
        default:
            return isdigit(peek) ? getNumericToken() : getIdentifierToken();
    }
}

