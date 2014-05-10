/**
 * What is the parser going to do?
 *
 * 1. Main is going to call parser with an istream.
 * 2. Parser creates an instance of the lexer with the istream
 *
 */
#include <istream>
#include <iostream>
#include <cassert>
#include "Debug.h"
#include "Parser.h"
#include "Lexer.h"
#include "Token.h"
#include "SeqAST.h"
#include "IfStmtAST.h"
#include "CallAST.h"
#include "ExprAST.h"
#include "ParamAST.h"
#include "FuncStmtAST.h"
#include "WhileStmtAST.h"
#include "IRBuilder.h"
#include "OPTok.h"

typedef std::shared_ptr<NodeAST> SNodeAST;
typedef std::shared_ptr<SeqAST> SSeqAST;

short GetPrecedence(SToken t) { 
    if(t->tag == Tags::BSQO) return 100;
    OPTok* opt = GUARD_CAST<OPTok*>(t.get());
    switch(opt->value){
        case OPC::LT: case OPC::LEQ: case OPC::GT: case OPC::GEQ: 
        case OPC::NEQ: case OPC::EQ: return 10;
        case OPC::BOR: return 20;
        case OPC::XOR: return 30;
        case OPC::BAND : return 40;
        case OPC::LSHIFT: case OPC::RSHIFT:  return 50;
        case OPC::ADD: case OPC::SUB:  return 60;
        case OPC::MULT: case OPC::DIV: case OPC::MOD:  return 70;
        case OPC::POWER: return 80;
        case OPC::INV: return 90;
        default: return 100;
    }
}

Parser::Parser(istream* i) {
    lexer = make_shared<Lexer>(i);
}

void Parser::move(){
    look = lexer->Scan();
}

SNodeAST Parser::Parse(){
    /*
     * Block => [Stmt]*
     * Stmt => ifStmt, tryStmt, forStmt, whileStmt...
     * ifStmt => 
     */
    move();
    return ParseBlock();
}



SNodeAST Parser::ParseFunctionParam(bool isCall = false){
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
    SNodeAST param;
    auto p = make_shared<ParamAST>();
    auto lw = GUARD_CAST<WordTok*>(look.get());
    switch(look->tag){
        case Tags::ID: case Tags::STR:
            p->AddParam(lw->value, nullptr);
            move();
            break;
        case Tags::PARAM:
            while(look->tag == Tags::PARAM){
                param = look;
                lw = GUARD_CAST<WordTok*>(look.get());
                move();
                //is it a [] grouping, only possible in a func call
                if(isCall && look->tag == Tags::BSQO){
                    p->AddParam(lw->value, ParseFunctionCall());
                }
                else if(look->tag == Tags::BCIO){
                    //is it a () grouping
                    if(!isCall) move(); //consume the (
                    //Seems to be a function
                    if(look->tag == Tags::PARAM) 
                        p->AddParam(lw->value, ParseFunctionParam());
                    else { p->AddParam(lw->value, ParseExpr()); }
                    if(!isCall) move(); //consume the ))
                }
                else if(look->tag == Tags::BCIC){
                    move(); break;
                }
                else{
                    //its a simple id
                    if(isCall){
                        p->AddParam(lw->value, ParseExpr());
                    }
                    else {
                        p->AddParam(lw->value, look);
                        move();
                    }
                }
            }
            break;
        default:
            assert(false);
            //throw an error. Function is malformed
    }
    return p;
}

/*
 *            CALL_N
 *       OBJ_N    PARAM_N
 *  
 */
SNodeAST Parser::ParseFunctionCall(){
    move(); //consume [
    auto call = make_shared<CallAST>();
    switch(look->tag){
        case Tags::PARAM:  //[call:2 withb:]
            call->SetRight(ParseFunctionParam(true));
            break;
        case Tags::BSQO: //[[obj init] doSmth:a]
            call->SetLeft(ParseFunctionCall());
            call->SetRight(ParseFunctionParam(true));
            break;
        case Tags::ID:
            call->SetLeft(look);
            move(); //consume the object
            call->SetRight(ParseFunctionParam(true)); //[obj some]
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
SNodeAST Parser::ParseFunctionStmt(){
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

    auto param = ParseFunctionParam();
    auto block = ParseBlock();
    auto funcDef = make_shared<FuncStmtAST>(param, block);

    //consume the endfun 
    //TODO use matchAndMove instead to make sure that the syntax is valid
    move();
    return funcDef;
}


SNodeAST Parser::ParseSingleStmt(){
    /*
     * var a = 2
     * var b = (2 + 2)
     * ac  = 2 //Error ac has not been declared
     * [smth]
     *
     */
    //[smth]
    if(look->tag == Tags::BSQO){ return ParseFunctionCall(); }
    SNodeAST node;

    if(look->tag == Tags::VAR){
        move();
        node = make_shared<NodeAST>(NodeType::VAR, look, nullptr);
        assert(look->tag == Tags::ID);
    }

    if(look->tag == Tags::ID){
        SToken tmp = look;
        move(); //move over the variable;
        //var a = smth
        if(look->tag == Tags::ASSIGN){
            move();
            auto n = make_shared<NodeAST>(NodeType::ASSIGN, tmp, ParseExpr());
            if(node.get() != nullptr){
                node->SetRight(n);
                return node;
            }
            else { return n; } //a = smth;
        } 
        else if(node.get() != nullptr) { return node; } //var a

        //TODO What if the single statement has a single variable only?
        assert(false);
    }

    //make sure that that the var keyword has not been found
    assert(node.get() == nullptr);
    assert(look->tag != Tags::ASSIGN);

    switch(look->tag){
        case Tags::RETURN:
            move();
            return make_shared<NodeAST>(NodeType::RETURN,ParseExpr(),nullptr);
            break;
    }
    
    assert(false);
    return node;
}

/*
 * Using the Shunting yard algorithm to turn the infix expr
 * to RPN
 *
 * TODO: Optimization - We can perform open expressions ourselves rather than
 * having the vm do it
 */
SNodeAST Parser::ParseExpr(){
    // Expr -> id
    // Expr -> Val 
    // Expr -> (Expr op epxr)
    uint currentLine = look->line;
    VecSTok opstack;
    VecSTok outstack;
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
                while(!opstack.empty()){
                    if(opstack.back()->tag == Tags::BCIO){
                        opstack.pop_back();
                        break;
                    }
                    outstack.push_back(opstack.back());
                    opstack.pop_back();
                }
                move(); 
                break;
            case Tags::BSQO:
            {
                SToken tmp = look;
                tmp->SetLeft(ParseFunctionCall());
                outstack.push_back(tmp);
                break;
            }
            case Tags::ID: case Tags::NUM: case Tags::REAL: case Tags::STR: 
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
    int count = outstack.size();
    if(count == 0) shared_ptr<NodeAST>(nullptr);
    return make_shared<ExprAST>(outstack);
}

/*
 *  if a 
 *      [do something]
 *  elif b
 *      [do something]
 *  else
 *      [do something]
 *  endif
 *
 *  if a 
 *
 *
 */
SNodeAST Parser::ParseIfStmt(){
    //ifStmt -> if (bool) block [elif block] [else block] endif
    //consume if
    move();
    auto stmt = make_shared<IfStmtAST>(ParseExpr(), ParseBlock());
    if(look->tag == Tags::ELIF){
        assert(false && "Not supported");
    }
    if(look->tag == Tags::ELSE){
        move();
        stmt->SetElseBlk(ParseBlock());
    }
    //consume endif
    move();
    return stmt;
}

SNodeAST Parser::ParseForStmt(){ return nullptr; } 

SNodeAST Parser::ParseTryStmt(){ return nullptr; }

SNodeAST Parser::ParseClassStmt(){ return nullptr; }

SNodeAST Parser::ParseWhileStmt(){ 
    //consume while
    move();
    auto stmt = make_shared<WhileStmtAST>(ParseExpr(), ParseBlock());
    //consume endwhile
    move();
    return stmt;
}

/*
 *                             SeqAST
 *                         STMT   SEQ
 *                              STMT  SEQ
 *                                 ...
 */
SNodeAST Parser::ParseBlock(){
    //Block -> Stmts...
    SSeqAST s = make_shared<SeqAST>();
    SSeqAST ts = s;
    SNodeAST tmp;
    while(true){
        switch(look->tag){
            //blocks
            case Tags::DEFCLASS: tmp = ParseClassStmt(); break;
            case Tags::DEFUN: tmp = ParseFunctionStmt(); break;
            case Tags::IF: tmp = ParseIfStmt(); break;
            case Tags::FOR: tmp = ParseForStmt(); break;
            case Tags::TRY: tmp = ParseTryStmt(); break;
            case Tags::WHILE: tmp = ParseWhileStmt(); break;
            //block ends
            case Tags::SEOF: case Tags::ENDIF: case Tags::ENDFOR:
            case Tags::ENDTRY: case Tags::ENDWHILE: case Tags::ENDCLASS:
            case Tags::ENDFUN: case Tags::ELSE: return ts;
            default:
                tmp = ParseSingleStmt();
        }
        s = s->AddSeq(tmp);
    }
    return ts;
}

