#include <string>
#include <istream>
#include <iostream>
#include <algorithm>
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
                     "OR", "NOT", "DIV", "ASSIGN", "DEFCLASS", "ENDCLASS", "DEFUN", "ENDFUN", 
                     "IF", "ELIF", "ELSE", "ENDIF", "WHILE", "ENDWHILE", "TRY", "CATCH", 
                     "ENDTRY", "WITH", "ENDWITH", "AS", "IN", "FOR", "ENDFOR", "VAR", "ISA",
                     "REAL", "ID", "DECR", "INCR", "BSQO", "BSQC", "SEOF", "STR", "BCIO", "BCIC",
                     "BCUC", "BCUO", "BLK", "ENDBLK", "CMD"};

/* debug stuff */
#define LEN_BLOCKTOKENS 9
string blockTokens[] = {"defclass", "defun", "if","elif","for","try","catch","else","while"};

#define LEN_ENDTOKENS 7
string endTokens[] = {"endif","endfor","endtry","endcatch","endwhile","endclass","endfun"};

#define LEN_CMDTOKENS 5
string cmdTokens [] = {"in", "var", "isa", "return", "break"};

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

Token* Lexer::parseSpecialNumber(){
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
        if(isHex) return new Number(decFromHex(tmp), Tags::NUM);
        else if(isHex) return new Number(decFromOct(tmp), Tags::NUM);
        else return new Number(decFromBin(tmp), Tags::NUM);
    }
    return new Number(0, Tags::NUM);
}

Token* Lexer::getNumericToken(){
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
    if(peek != '.') return new Number(decFromDec(tmp), Tags::NUM);

    //handle real numbers
    tmp += ".";
    do{
        readChar();
        tmp += peek;
    }while(isdigit(peek));
    return new Real(floatFromFloat(tmp), Tags::REAL);
}

Token* Lexer::getIdentifierToken(){
    string tmp;
    while(isalpha(peek) || peek == ':' || isdigit(peek)){
        tmp += peek;  
        readChar();
    }
    if(count(blockTokens, blockTokens + LEN_BLOCKTOKENS, tmp) > 0)
        return new Word(tmp, Tags::BLK);
    else if(count(endTokens, endTokens + LEN_ENDTOKENS, tmp) > 0)
        return new Word(tmp, Tags::ENDBLK);
    else if(count(cmdTokens, cmdTokens + LEN_CMDTOKENS, tmp) > 0)
        return new Word(tmp, Tags::CMD);
    else
        return new Word(tmp, Tags::ID);
}

//TODO
void Lexer::printAll(){
    while(true){
        Token* newtok = scan();
        if(newtok->tag == Tags::SEOF) exit(0);
        /*
        */
        if(debugCounter++ > 30){
            exit(0);
        }
        delete newtok;
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
    if(readAndMatch(match)){ return new Token(ifMatch); } \
    else{ return new Token(elseMatch); }

#define IFMATCHELIFELSE(match, ifMatch, matchElif, elifMatch, elseMatch) \
    if(readAndMatch(match)){ return new Token(ifMatch); } \
    else if(peek == matchElif) { return new Token(elifMatch); } \
    else{ return new Token(elseMatch); }

Token* Lexer::scan(){
    //Get rid of the white space
    for(;;readChar()){
        if(peek == '\n') { cout << endl; } //line += 1;
        else if(isspace(peek)){ continue; }
        else { break; }
    }
    switch(peek){
        case '&': IFMATCHELSE('&', Tags::AND, Tags::BAND);
        case '|': IFMATCHELSE('|', Tags::OR, Tags::BOR);
        case '-': IFMATCHELSE('-', Tags::DECR, Tags::MINUS);
        case '+': IFMATCHELSE('+', Tags::INCR, Tags::PLUS);
        case '*': IFMATCHELSE('*', Tags::POW, Tags::MULT);
        case '/': readChar(); return new Token(Tags::DIV);
        case '!': IFMATCHELSE('=', Tags::NEQ, Tags::NOT);
        case '~': readChar(); return new Token(Tags::BNOT);
        case '^': readChar(); return new Token(Tags::BXOR);
        case '<': IFMATCHELIFELSE('=', Tags::LTE, '<', Tags::LSHIFT, Tags::LT);
        case '>': IFMATCHELIFELSE('=', Tags::GTE, '>', Tags::RSHIFT, Tags::GT);
        case '=': IFMATCHELSE('=', Tags::EQ, Tags::ASSIGN);
        case '[': readChar(); return new Token(Tags::BSQO);
        case ']': readChar(); return new Token(Tags::BSQC);
        case '(': readChar(); return new Token(Tags::BCIO);
        case ')': readChar(); return new Token(Tags::BCIC);
        case '{': readChar(); return new Token(Tags::BCUO);
        case '}': readChar(); return new Token(Tags::BCUC);
        case '"': return parseStringLiteral();
        case -1: return new Token(Tags::SEOF);
        default:
            return isdigit(peek) ? getNumericToken() : getIdentifierToken();
    }
}

Token* Lexer::parseStringLiteral(){
    readChar();
    string tmp;
    do{
        tmp += peek;
    } while(!readAndMatch('"'));
    return new Word(tmp, Tags::STR);
}

