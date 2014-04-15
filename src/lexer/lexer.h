#ifndef T_LEXER_H
#define T_LEXER_H
#include <string>
#include <istream>
#include <unordered_map>
#include "token.h"
#include "word.h"
#include "number.h"
#include "real.h"
using std::string;
using std::istream;

typedef std::unordered_map<string, Token> IDTable;
class Lexer {
private:
    char peek;
    IDTable words;
    void reserve(Word w) { /*words[w.lexeme] = w;*/ }
    istream* inputStream;

    Token getNumericToken(){
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
        return Real(decFromFloat(tmp), Tags::REAL);
    }

    Token getIdentifierToken(){
        string tmp;
        while(isalpha(peek) || peek == ':' || isdigit(peek)){
            tmp += peek;  
            readChar();
        }
        return Word(tmp, Tags::ID);
    }

    int decFromHex(string hexStr){
        return 0;
    }

    int decFromOct(string octStr){
        return 0;
    }

    int decFromBin(string binStr){
        return 0;
    }

    int decFromDec(string decStr){
        return 0;
    }

    double decFromFloat(string floatStr){
        return 0;
    }

public: 
    void printAll() {}
    Lexer(istream pistream) { inputStream = &pistream; peek = ' '; }
    void readChar() { *inputStream >> peek; }
    bool readCharAndMatch(char ch) { 
        readChar();
        if(peek != ch){ return false; }
        peek = ' ';
        return true;
    } 

    Token scan() {
        //Get rid of the white space
        for(;;readChar()){
            if(peek == '\n') {} //line += 1;
            else if(!isspace(peek)){ continue; }
            else { break; }
        }
        switch(peek){
            case '&':
                if(readCharAndMatch('&')){ return Word("&&", Tags::AND); }
                else{ return Word("&", Tags::BAND); }
            case '|':
                if(readCharAndMatch('|')){ return Word("||", Tags::OR); }
                else{ return Word("|", Tags::BOR); }
            case '-':
                if(readCharAndMatch('-')){ return Word("--", Tags::DECR); }
                else{ return Word("-", Tags::MINUS); }
            case '+':
                if(readCharAndMatch('+')){ return Word("++", Tags::INCR); }
                else{ return Word("+", Tags::PLUS); }
            case '*':
                if(readCharAndMatch('*')){ return Word("**", Tags::POW); }
                else{ return Word("*", Tags::MULT); }
            case '/':
                return Word("/", Tags::DIV);
            case '!':
                if(readCharAndMatch('=')){ return Word("!=", Tags::NEQ); }
                else { return Word("!", Tags::NOT); }
            case '~':
                return Word("~", Tags::BNOT);
            case '^':
                return Word("^", Tags::BXOR);
            case '<':
                if(readCharAndMatch('=')){ return Word("<=", Tags::LTE); }
                else if(readCharAndMatch('<')) { return Word("<<", Tags::LSHIFT); }
                else{ return Word("<", Tags::LT); }
            case '>':
                if(readCharAndMatch('=')){ return Word(">=", Tags::GTE); }
                else if(readCharAndMatch('>')) { return Word(">>", Tags::RSHIFT); }
                else{ return Word(">", Tags::GT); }
            case '=':
                if(readCharAndMatch('=')){ return Word("==", Tags::EQ); }
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
};

#endif
