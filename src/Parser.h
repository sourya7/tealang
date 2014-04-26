#ifndef T_PARSER_H
#define T_PARSER_H
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
#include <string>
#include <map>
#include "NodeAST.h"
#include "Lexer.h"
#include "Token.h"

using namespace std;

class Parser {
private:
    Token* look;
    Lexer* lexer;
    map<string, short> precedence;
public:
    Parser(istream* i);
    void move();

    NodeAST* Parse();
    NodeAST* ParseBlock();
    NodeAST* ParseIfStmt();
    NodeAST* ParseForStmt();
    NodeAST* ParseTryStmt();
    NodeAST* ParseClassStmt();
    NodeAST* ParseWhileStmt();
    NodeAST* ParseSingleStmt();
    NodeAST* ParseFunctionStmt();
    NodeAST* ParseFunctionParam(bool isCall);
    NodeAST* ParseFunctionCall();

    short GetPrecedence(Token* t);
    NodeAST* ParseExpr();
};

#endif
