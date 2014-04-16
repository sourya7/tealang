#include <string>
#include <istream>
#include <map>
#include "token.h"
#include "word.h"
#include "number.h"
#include "real.h"
#include "lexer.h"

using std::string;
using std::istream;

Token Lexer::getNumericToken(){
    if(peek == 0){
        readChar();
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
    
    //handle decimal numbers
    string tmp;
    do{
        tmp += peek;
        readChar();
    }while(isdigit(peek));

    if(peek != '.') return Number(decFromDec(tmp), Tags::NUM);
    //handle real numbers
    do{
        tmp += peek;
        readChar();
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

int Lexer::decFromHex(string hexStr){
    return 0;
}

int Lexer::decFromOct(string octStr){
    return 0;
}

int Lexer::decFromBin(string binStr){
    return 0;
}

int Lexer::decFromDec(string decStr){
    return 0;
}

double Lexer::floatFromFloat(string floatStr){
    return 0;
}

void Lexer::printAll() {}

Lexer::Lexer(istream pistream) { inputStream = &pistream; peek = ' '; }

void Lexer::readChar() { *inputStream >> peek; }

bool Lexer::readAndMatch(char ch) { 
    readChar();
    if(peek != ch){ return false; }
    peek = ' ';
    return true;
} 

Token Lexer::scan() {
    //Get rid of the white space
    for(;;readChar()){
        if(peek == '\n') {} //line += 1;
        else if(!isspace(peek)){ continue; }
        else { break; }
    }
    switch(peek){
        case '&':
            if(readAndMatch('&')){ return Word("&&", Tags::AND); }
            else{ return Word("&", Tags::BAND); }
        case '|':
            if(readAndMatch('|')){ return Word("||", Tags::OR); }
            else{ return Word("|", Tags::BOR); }
        case '-':
            if(readAndMatch('-')){ return Word("--", Tags::DECR); }
            else{ return Word("-", Tags::MINUS); }
        case '+':
            if(readAndMatch('+')){ return Word("++", Tags::INCR); }
            else{ return Word("+", Tags::PLUS); }
        case '*':
            if(readAndMatch('*')){ return Word("**", Tags::POW); }
            else{ return Word("*", Tags::MULT); }
        case '/':
            return Word("/", Tags::DIV);
        case '!':
            if(readAndMatch('=')){ return Word("!=", Tags::NEQ); }
            else { return Word("!", Tags::NOT); }
        case '~':
            return Word("~", Tags::BNOT);
        case '^':
            return Word("^", Tags::BXOR);
        case '<':
            if(readAndMatch('=')){ return Word("<=", Tags::LTE); }
            else if(readAndMatch('<')) { return Word("<<", Tags::LSHIFT); }
            else{ return Word("<", Tags::LT); }
        case '>':
            if(readAndMatch('=')){ return Word(">=", Tags::GTE); }
            else if(readAndMatch('>')) { return Word(">>", Tags::RSHIFT); }
            else{ return Word(">", Tags::GT); }
        case '=':
            if(readAndMatch('=')){ return Word("==", Tags::EQ); }
            else{ return Word("=", Tags::ASSIGN); }
        case '[':
            return Word("[", Tags::BSQO);
        case ']':
            return Word("]", Tags::BSQC);
        default:
            if(isdigit(peek)){
                return getNumericToken();
            }
            else{
                return getIdentifierToken();
            }
    }
}

