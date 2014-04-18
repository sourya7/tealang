/**
 * What is the parser going to do?
 *
 * 1. Main is going to call parser with an istream.
 * 2. Parser creates an instance of the lexer with the istream
 *
 */
#include <istream>
#include <iostream>
#include "lexer.h"
#include "ltoken.h"

using namespace std;

class TParser {
private:
    Token* look;
    Lexer* lexer;
public:
    TParser(istream* i) {
        lexer = new Lexer(inputStream);
    }

    void move(){
        look = lexer->Scan();
    }
    
    void Parse(){
        /*
         * Block => [Stmt]*
         * Stmt => ifStmt, tryStmt, forStmt, whileStmt...
         * ifStmt => 
         */
        ParseBlock();
    }

    void ParseFunctionStmt(){
        /*
         * defun bla
         *    [print: something]
         * endfun
         * 
         * defun funWith:a andB:b
         * defun funWith:(funWithA:B:) andB:b
         * endfun
         */
        Word* tok = (Word*)lexer->Next();
        
    }

    void ParseBlock(){
        Token* tok = lexer->Next();
        switch(tok->tag){
            case Tags::BLK:
                Word* word = (Word*)tok;
                if(word->lexeme == "defun") ParseFunctionStmt(); 
                else if(word->lexeme == "defclass") ParseFunctionStmt(); 
                else if(word->lexeme == "if") ParseFunctionStmt(); 
                else if(word->lexeme == "for") ParseFunctionStmt(); 
                else if(word->lexeme == "try") ParseFunctionStmt(); 
                else if(word->lexeme == "while") ParseFunctionStmt(); 
            case 
        }
    }
};

class Node {
protected:
    vector<Node*> nodes;
    Tags tag;

public:
    Node() {} 
}
