/**
 * What is the parser going to do?
 *
 * 1. Main is going to call parser with an istream.
 * 2. Parser creates an instance of the lexer with the istream
 *
 */
#include <istream>
#include <iostream>
#include "parser.h"
#include "lexer.h"
#include "ltoken.h"

using namespace std;

TParser::TParser(istream* i) {
    lexer = new Lexer(i);
}

void TParser::move(){
    cin.get();
    look = lexer->Scan();
    Word* tok = dynamic_cast<Word*>(look);
    if(tok != nullptr) 
        cout << tok->lexeme;
}

void TParser::Parse(){
    /*
     * Block => [Stmt]*
     * Stmt => ifStmt, tryStmt, forStmt, whileStmt...
     * ifStmt => 
     */
    move();
    ParseBlock();
}

void TParser::ParseFunctionParam(){
    //1. Functions can have no parameter
    //   defun bla 
    //      [print: Hello]
    //   endfun
    //2. Functions can have one or more parameter
    //   defun blaWithA:a andB:b
    //      [print: a+b]
    //   endfun
    //
    //3. Functions can have other functions as param
    //   defun funcWithCb:(cb:a andB:b) andB:b
    //      //do something
    //   endfun
    uint currentLine = look->line;
    switch(look->tag){
        case Tags::ID:
            move(); //consume it
            //We have a single parameter
        case Tags::PARAM:
            while(look->line == currentLine){
                //get the next token
                move();
                //is it a () grouping
                if(look->tag == Tags::BCIO){
                    move(); //consume the (
                    //Seems to be a function
                    if(look->tag == Tags::PARAM) ParseFunctionParam();
                    // TODO may be it's an expression
                    move(); //consume the )
                }
                else if(look->tag == Tags::BCIC){
                    //I am in a recursive function. Lets leave
                    //consume the )
                    move();
                    break;
                }
                else{
                    //its a simple id
                    move();
                }
            }
            //we have a parameter
        default:
            cout << "Error!!!";
            //throw an error. Function is malformed
    }
}

void TParser::ParseFunctionStmt(){
    /*
     * defun bla
     *    [print: something]
     * endfun
     * 
     * defun funWith:a andB:b
     * defun funWith:(funWithA:B:) andB:b
     * endfun
     */
    //consume defun
    move(); 
    ParseFunctionParam();
    ParseBlock();
    //consume the endfun 
    //TODO use matchAndMove instead to make sure that the syntax is valid
    move();
}

void TParser::ParseBlock(){
    switch(look->tag){
        case Tags::BLK:
            Word* word = (Word*)look;
            if(word->lexeme == "defun") ParseFunctionStmt(); 
            else if(word->lexeme == "defclass") ParseFunctionStmt(); 
            else if(word->lexeme == "if") ParseFunctionStmt(); 
            else if(word->lexeme == "for") ParseFunctionStmt(); 
            else if(word->lexeme == "try") ParseFunctionStmt(); 
            else if(word->lexeme == "while") ParseFunctionStmt(); 
    }
}

