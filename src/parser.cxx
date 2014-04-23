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
    Word* word = dynamic_cast<Word*>(look);
    if(word != nullptr){
        cerr << "\nLine: " << look->line << " "; 
        cerr << " <id," << word->lexeme << ">  \t";
    }
    else if(look != nullptr) {
        cerr << "\nLine: " << look->line << " "; 
        cerr << " <tok," << (int)look->tag << ">  \t";
    }
    look = lexer->Scan();
}

void TParser::Parse(){
    /*
     * Block => [Stmt]*
     * Stmt => ifStmt, tryStmt, forStmt, whileStmt...
     * ifStmt => 
     */
    move();
    cerr << "Parse()";
    ParseBlock();
    cerr << "";
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
            cerr << "ParseFunctionParam::ID ()";
            break;
            //We have a single parameter
        case Tags::PARAM:
            while(look->tag == Tags::PARAM){
                //get the next token
                move();
                cerr << "ParseFunctionParam::PARAM ()";
                //is it a () grouping
                if(look->tag == Tags::BCIO){
                    move(); //consume the (
                    cerr << "ParseFunctionParam::BCIO ()";
                    //Seems to be a function
                    if(look->tag == Tags::PARAM) ParseFunctionParam();
                    // TODO may be it's an expression
                    move(); //consume the )
                    cerr << "ParseFunctionParam::BCIO()";
                }
                else if(look->tag == Tags::BCIC){
                    //I am in a recursive function. Lets leave
                    //consume the )
                    move();
                    break;
                    cerr << "ParseFunctionParam::BCIC()";
                }
                else{
                    //its a simple id
                    move();
                    cerr << "ParseFunctionParam::ELSE ()";
                }
            }
            break;
            //we have a parameter
        default:
            cerr << "Error!!!";
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
    cerr << "ParseFunctionStmt ()";
    ParseFunctionParam();
    ParseBlock();
    //consume the endfun 
    //TODO use matchAndMove instead to make sure that the syntax is valid
    move();
    cerr << "ParseFunctionStmt ()";
}

void TParser::ParseSingleStmt(){
    uint currentLine = look->line;
    while(currentLine == look->line){
        move();
        cerr << "ParseSingleStmt ()";
    }
}

void TParser::ParseExpr(){
    // Expr -> id
    // Expr -> Val 
    // Expr -> (Expr op epxr)
    // abc = 2 + 2
    uint currentLine = look->line;
    while(currentLine == look->line){
        switch(look->tag){
            case Tags::BCIO:
                move(); //consume (
                cerr << "ParseExpr::BCIO ()";
                ParseExpr();
                break;
            case Tags::BCIC:
                move(); //consume )
                cerr << "ParseExpr::BCIC ()";
                return;
            case Tags::ID: case Tags::NUM: case Tags::REAL:
                move(); //consume it
                cerr << "ParseExpr::ID ()";
                break;
            case Tags::OP:
                move();
                cerr << "ParseExpr::OP ()";
                break;
            default:
                move();
                cerr << "ParseExpr::DEF()";
                break;
                //'a' '==' 'b'
        }
    }
}

void TParser::ParseIfStmt(){
    //ifStmt -> if (bool) block [elif block] [else block] endif
    //consume if
    move();
    cerr << "ParseIfStmt ()";
    ParseExpr();
    ParseBlock();
    //consume endif
    move();
}
void TParser::ParseForStmt(){}
void TParser::ParseTryStmt(){}
void TParser::ParseClassStmt(){}
void TParser::ParseWhileStmt(){}

void TParser::ParseBlock(){
    //Block -> Stmts...
    while(true){
        switch(look->tag){
            case Tags::BLK:{
                Word* word = (Word*)look;
                if(word->lexeme == "defun") ParseFunctionStmt(); 
                else if(word->lexeme == "defclass") ParseClassStmt(); 
                else if(word->lexeme == "if") ParseIfStmt(); 
                else if(word->lexeme == "for") ParseForStmt(); 
                else if(word->lexeme == "try") ParseTryStmt(); 
                else if(word->lexeme == "while") ParseWhileStmt(); 
                break;
            }
            case Tags::SEOF: case Tags::ENDBLK:
                return;
            default:
                ParseSingleStmt();
        }
    }
}

