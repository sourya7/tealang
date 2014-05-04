#include <string>
#include <istream>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <sstream>
#include "Token.h"
#include "WordTok.h"
#include "NumberTok.h"
#include "RealTok.h"
#include "OPTok.h"
#include "OPCode.h"
#include "Lexer.h"

using namespace std;

/* debug stuff */
map<string, Tags> TokenMap {
    {"defclass", Tags::DEFCLASS},
    {"defun", Tags::DEFUN},
    {"if", Tags::IF},
    {"for", Tags::FOR},
    {"try", Tags::TRY},
    {"while", Tags::WHILE},
    {"elif", Tags::ELIF},
    {"catch", Tags::CATCH},
    {"else", Tags::ELSE},
    {"endif", Tags::ENDIF},
    {"endfor", Tags::ENDFOR},
    {"endtry", Tags::ENDTRY},
    {"endwhile", Tags::ENDWHILE},
    {"endclass", Tags::ENDCLASS},
    {"endfun", Tags::ENDFUN},
    {"in", Tags::IN},
    {"var", Tags::VAR},
    {"isa", Tags::ISA},
    {"return", Tags::RETURN},
    {"break", Tags::BREAK }
};

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

int decFromDec(string decStr){  
    return atoi(decStr.c_str());
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
    if(peek != '.') return new NumberTok(decFromDec(tmp), line);

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
    auto it = TokenMap.find(tmp);
    if(peek == ':') { ReadChar(); tmp += ':'; tag = Tags::PARAM; }
    else if(it != TokenMap.end()){
        tag = it->second;
        /*
        switch(it->second){
            case Tags::DEFCLASS:
            case Tags::DEFUN:
            case Tags::IF:
            case Tags::FOR:
            case Tags::TRY:
            case Tags::WHILE:
            case Tags::ELIF:
            case Tags::CATCH:
            case Tags::ELSE:
            case Tags::ENDIF:
            case Tags::ENDFOR:
            case Tags::ENDTRY:
            case Tags::ENDWHILE:
            case Tags::ENDCLASS:
            case Tags::ENDFUN:
            case Tags::IN:
            case Tags::VAR:
            case Tags::ISA:
            case Tags::RETURN:
            case Tags::BREAK:
        }
        */
        return new Token(tag, line);
    }
    else {
        tag = Tags::ID;
    }

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
        case '&': { IFMATCHELSE('&', OPC::AND, OPC::BAND); } 
        case '|': { IFMATCHELSE('|', OPC::OR, OPC::BOR); } 
        case '-': { IFMATCHELSE('-', OPC::DECR, OPC::SUB); }
        case '+': { IFMATCHELSE('+', OPC::INCR, OPC::ADD); }
        case '*': { IFMATCHELSE('*', OPC::POWER, OPC::MULT); }
        case '!': { IFMATCHELSE('=', OPC::NEQ, OPC::NOT); }
        case '<': { IFMATCH2ELSE('=', OPC::LEQ, '<', OPC::LSHIFT, OPC::LT); }
        case '>': { IFMATCH2ELSE('=', OPC::GEQ, '>', OPC::RSHIFT, OPC::GT); }
        case '/': { ReadChar(); return new OPTok(OPC::DIV, line); }
        case '%': { ReadChar(); return new OPTok(OPC::MOD, line); }
        case '~': { ReadChar(); return new OPTok(OPC::INV, line);  }
        case '^': { ReadChar(); return new OPTok(OPC::XOR, line); }
        case '[': { ReadChar(); return new Token(Tags::BSQO, line);   }
        case ']': { ReadChar(); return new Token(Tags::BSQC, line);   }
        case '(': { ReadChar(); return new Token(Tags::BCIO, line);   }
        case ')': { ReadChar(); return new Token(Tags::BCIC, line);   }
        case '{': { ReadChar(); return new Token(Tags::BCUO, line);   }
        case '}': { ReadChar(); return new Token(Tags::BCUC, line);   }
        case '"': case '\'': { return ParseStringLiteral(); } 
        case -1: { return new Token(Tags::SEOF, line); }
        case '=': { if(ReadAndMatch('=')) return new OPTok(OPC::EQ, line);
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
        if(quote == '"' && tmp.back() == '\\'){
            tmp.pop_back();
            switch(peek){
                case 'a': tmp += 7; break;
                case 'b': tmp += 8; break;
                case 'e': tmp += 27; break;
                case 'f': tmp += 12; break;
                case 'n': tmp += 10; break;
                case 'r': tmp += 13; break;
                case 't': tmp += 9; break;
                case 'v': tmp += 11; break;
            }
        }
        else tmp += peek;
    } while(!ReadAndMatch(quote));
    return new WordTok(tmp, Tags::STR, line);
}

