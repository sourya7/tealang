#include <string>
#include <istream>
#include <iostream>
#include <map>
#include "token.h"
#include "word.h"
#include "number.h"
#include "real.h"
#include "lexer.h"

using namespace std;

/* TODO - Remove after I'm done with the lexer
 * Just for debugging purposes */
string mTagNames[] = {"BAND", "BOR", "BNOT", "BXOR", "PLUS", "MINUS", "MULT", "POW",
                     "MOD", "NUM", "LSHIFT", "RSHIFT", "LTE", "GTE", "LT", "GT", "EQ", "NEQ", "AND",
                     "OR", "NOT", "DIV", "ASSIGN", "DEFCLASS", "ENDCLASS", "DEFFUN", "ENDFUN", 
                     "IF", "ELIF", "ELSE", "ENDIF", "WHILE", "ENDWHILE", "TRY", "CATCH", 
                     "ENDTRY", "WITH", "ENDWITH", "AS", "IN", "FOR", "ENDFOR", "VAR", "ISA",
                     "REAL", "ID", "DECR", "INCR", "BSQO", "BSQC", "SEOF", "STR", "BCRO", "BCRC"};
/* debug stuff */


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

//TODO
void Lexer::printAll(){
    while(true){
        debugCounter++;
        Token newtok = scan();
        if(newtok.tag == Tags::SEOF) exit(0);
        if(newtok.tag == Tags::ID || newtok.tag == Tags::NUM || newtok.tag == Tags::REAL){
        }
        else{
        }
    }
}

Lexer::Lexer(istream& pistream){ 
    inputStream = &pistream; 
    peek = ' '; 
}

void Lexer::readChar(){ 
    bool res = inputStream->get(peek); 
    if(!res) peek = -1;
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
        else if(isspace(peek)){ continue; }
        else { break; }
    }
    switch(peek){
        case '&': IFMATCHELSE('&', Tags::AND, Tags::BAND);
        case '|': IFMATCHELSE('|', Tags::OR, Tags::BOR);
        case '-': IFMATCHELSE('-', Tags::DECR, Tags::MINUS);
        case '+': IFMATCHELSE('+', Tags::INCR, Tags::PLUS);
        case '*': IFMATCHELSE('*', Tags::POW, Tags::MULT);
        case '/': readChar(); return Token(Tags::DIV);
        case '!': IFMATCHELSE('=', Tags::NEQ, Tags::NOT);
        case '~': readChar(); return Token(Tags::BNOT);
        case '^': readChar(); return Token(Tags::BXOR);
        case '<': IFMATCHELIFELSE('=', Tags::LTE, '<', Tags::LSHIFT, Tags::LT);
        case '>': IFMATCHELIFELSE('=', Tags::GTE, '>', Tags::RSHIFT, Tags::GT);
        case '=': IFMATCHELSE('=', Tags::EQ, Tags::ASSIGN);
        case '[': readChar(); return Token(Tags::BSQO);
        case ']': readChar(); return Token(Tags::BSQC);
        case '(': readChar(); return Token(Tags::BCRO);
        case ')': readChar(); return Token(Tags::BCRC);
        case '"': return parseStringLiteral();
        case -1: return Token(Tags::SEOF);
        default:
            return isdigit(peek) ? getNumericToken() : getIdentifierToken();
    }
}

Token Lexer::parseStringLiteral(){
    readChar();
    string tmp;
    do{
        tmp += peek;
    } while(!readAndMatch('"'));
    return Word(tmp, Tags::STR);
}

