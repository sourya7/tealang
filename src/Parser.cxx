/**
 * What is the parser going to do?
 *
 * 1. Main is going to call parser with an istream.
 * 2. Parser creates an instance of the lexer with the istream
 *
 */
#include <istream>
#include <iostream>
#include <vector>
#include <cassert>
#include "Parser.h"
#include "Lexer.h"
#include "Token.h"
#include "SeqAST.h"
#include "IfStmtAST.h"
#include "ExprAST.h"
#include "IRBuilder.h"
#include "OPTok.h"
using namespace std;

short GetPrecedence(Token* t) { 
    OPTok* opt = dynamic_cast<OPTok*>(t);
    if(opt == nullptr) return 0;

    switch(opt->value){
        case OP::LT: case OP::LEQ: case OP::GT: case OP::GEQ: 
        case OP::NEQ: case OP::EQ: return 10;
        case OP::BOR: return 20;
        case OP::XOR: return 30;
        case OP::BAND : return 40;
        case OP::LSHIFT: case OP::RSHIFT:  return 50;
        case OP::ADD: case OP::SUB:  return 60;
        case OP::MULT: case OP::DIV: case OP::MOD:  return 70;
        case OP::POWER: return 80;
        case OP::INV: return 90;
        default: return 100;
    }
}


Parser::Parser(istream* i) {
    lexer = new Lexer(i);
    }

void Parser::move(){
    WordTok* word = dynamic_cast<WordTok*>(look);
    look = lexer->Scan();
}

NodeAST* Parser::Parse(){
    /*
     * Block => [Stmt]*
     * Stmt => ifStmt, tryStmt, forStmt, whileStmt...
     * ifStmt => 
     */
    move();
    return ParseBlock();
}

NodeAST* Parser::ParseFunctionParam(bool isCall = false){
    //1. Functions can have no parameter
    //   defun bla 
    //      [print: Hello]
    //   endfun
    //2. Functions can have one or more parameter
    //   defun blaWithA:a andB:b
    //      [print: a+b]
    //      [print: a + b andB:
    //   endfun
    //
    //3. Functions can have other functions as param
    //   defun funcWithCb:(cb:a andB:b) andB:b
    //      //do something
    //   endfun
    uint currentLine = look->line;
    SeqAST* seq = new SeqAST();
    SeqAST* tseq = seq;
    NodeAST* param;
    
    /*
    */
    switch(look->tag){
        case Tags::ID:
            seq = seq->AddSeq(look);
            move();
            return param;
        case Tags::PARAM:
            while(look->tag == Tags::PARAM){
                param = look;
                move();
                //is it a () grouping
                if(look->tag == Tags::BCIO){
                    if(!isCall) move(); //consume the (
                    //Seems to be a function
                    if(look->tag == Tags::PARAM) 
                        seq = seq->AddSeq(new NodeAST(NodeType::PARAM, param, ParseFunctionParam()));
                    else seq = seq->AddSeq(new NodeAST(NodeType::PARAM, param, ParseExpr()));
                    if(!isCall) move(); //consume the ))
                }
                else if(look->tag == Tags::BCIC){
                    move(); break;
                }
                else{
                    //its a simple id
                    seq = seq->AddSeq(new NodeAST(NodeType::PARAM, param, look));
                    move();
                }
            }
            break;
        default:
            assert(false);
            //throw an error. Function is malformed
    }
    return tseq;
}

/*
 *            CALL_N
 *       OBJ_N    PARAM_N
 *  
 */
NodeAST* Parser::ParseFunctionCall(){
    move(); //consume [
    NodeAST* call = new NodeAST(NodeType::CALL);
    switch(look->tag){
        case Tags::PARAM:  //[call:2 withb:]
            call->SetRight(ParseFunctionParam(true));
            break;
        case Tags::BSQO: //[[obj init] doSmth:a]
            call->SetLeft(ParseFunctionCall());
            call->SetRight(ParseFunctionParam());
            break;
        case Tags::ID:
            call->SetLeft(look);
            move(); //consume the object
            call->SetRight(ParseFunctionParam()); //[obj some]
        default:
            assert(false);
    }
    move(); //consume the ending ']'
    return call;
}

/*
 *       F_NODE
 *   FPAR_N  F_BLOCK
 *
 */
NodeAST* Parser::ParseFunctionStmt(){
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

    NodeAST* funcDef = new NodeAST(NodeType::FSTMT, ParseFunctionParam(), ParseBlock());

    //consume the endfun 
    //TODO use matchAndMove instead to make sure that the syntax is valid
    move();
    return funcDef;
}

NodeAST* Parser::ParseSingleStmt(){
    NodeAST* node;
    /*
     * var a = 2
     * var b = (2 + 2)
     * ac  = 2 //Error ac has not been declared
     * [smth]
     *
     */
    // Var* var = nullptr;
    if(look->tag == Tags::VAR){
        move();
        //var = new Var(look);
    }
    if(look->tag == Tags::ID){
        Token* tmp = look;
        move(); //move over the variable;
        if(look->tag == Tags::ASSIGN){
            move();
            node = new NodeAST(NodeType::ASSIGN, tmp, ParseExpr());
        }
    }
    else if(look->tag == Tags::BSQO){
        node = ParseFunctionCall();
    }
    else{
        assert(false);
    }

    //if(var != nullptr) var->scope(node);
    return node;
}

/*
 * Using the Shunting yard algorithm to turn the infix expr
 * to RPN
 */
NodeAST* Parser::ParseExpr(){
    // Expr -> id
    // Expr -> Val 
    // Expr -> (Expr op epxr)
    uint currentLine = look->line;
    vector<Token*> opstack;
    vector<Token*> outstack;
    bool stop = false;
    // Stop is needed for cases when the expression does not extend whole line
    // Eg. [someFunc: (a+b) ano:b] 
    // Here we dont stop at the end of the line, but when we reach the 
    // "ano:" PARAM
    while(!stop && (currentLine == look->line)){
        switch(look->tag){
            case Tags::BCIO:
                opstack.push_back(look);
                move(); //consume (
                break;
            case Tags::BCIC:
                while(!opstack.empty() && (opstack.back()->tag != Tags::BCIO)){
                    outstack.push_back(opstack.back());
                    opstack.pop_back();
                }
                move(); 
                break;
            case Tags::ID: case Tags::NUM: case Tags::REAL: 
                outstack.push_back(look); 
                move(); 
                break;
            case Tags::OP:
                while(!opstack.empty() && (opstack.back()->tag != Tags::BCIO)){
                    if(GetPrecedence(look) <= GetPrecedence(opstack.back())){
                        outstack.push_back(opstack.back());
                        opstack.pop_back();
                    }
                    else break;
                }
                opstack.push_back(look);
                move();
                break;
            default:
                stop = true; break;
        }
    }
    for(auto v : opstack) outstack.push_back(v);
    return new ExprAST(outstack);
}

NodeAST* Parser::ParseIfStmt(){
    //ifStmt -> if (bool) block [elif block] [else block] endif
    //consume if
    move();
    IfStmtAST* stmt = new IfStmtAST(ParseExpr(), ParseBlock());
    //TODO: Parse the elif and else stmts
    //consume endif
    move();
    return stmt;
}

NodeAST* Parser::ParseForStmt(){ return nullptr; } 

NodeAST* Parser::ParseTryStmt(){ return nullptr; }

NodeAST* Parser::ParseClassStmt(){ return nullptr; }

NodeAST* Parser::ParseWhileStmt(){ return nullptr; }

/*
 *                             SeqAST
 *                         STMT   SEQ
 *                              STMT  SEQ
 *                                 ...
 */
NodeAST* Parser::ParseBlock(){
    //Block -> Stmts...
    SeqAST* s = new SeqAST();
    SeqAST* ts = s;
    NodeAST* tmp;
    while(true){
        switch(look->tag){
            case Tags::BLK:{
                WordTok* word = static_cast<WordTok*>(look);
                if(word->value == "defun") tmp = ParseFunctionStmt(); 
                else if(word->value == "defclass") tmp = ParseClassStmt(); 
                else if(word->value == "if") tmp = ParseIfStmt(); 
                else if(word->value == "for") tmp = ParseForStmt(); 
                else if(word->value == "try") tmp = ParseTryStmt(); 
                else if(word->value == "while") tmp = ParseWhileStmt(); 
                break;
            }
            case Tags::SEOF: case Tags::ENDBLK:
                return ts;
            default:
                tmp = ParseSingleStmt();
        }
        s = s->AddSeq(tmp);
    }
    return ts;
}

