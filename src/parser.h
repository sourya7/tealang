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
#include "seq.h"
#include "node.h"
#include "lexer.h"
#include "ltoken.h"

using namespace std;

class TParser {
private:
    Token* look;
    Lexer* lexer;
    map<string, short> precedence;
public:
    TParser(istream* i);
    void move();

    Node* Parse();
    Node* ParseBlock();
    Node* ParseIfStmt();
    Node* ParseForStmt();
    Node* ParseTryStmt();
    Node* ParseClassStmt();
    Node* ParseWhileStmt();
    Node* ParseSingleStmt();
    Node* ParseFunctionStmt();
    Node* ParseFunctionParam(bool isCall);
    Node* ParseFunctionCall();

    short GetPrecedence(Token* t);
    Node* ParseExpr();
};

#endif
