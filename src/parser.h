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
#include "lexer.h"
#include "ltoken.h"

using namespace std;

class TParser {
private:
    Token* look;
    Lexer* lexer;
public:
    TParser(istream* i);
    void move();
    void Parse();
    void ParseExpr();
    void ParseBlock();
    void ParseIfStmt();
    void ParseForStmt();
    void ParseTryStmt();
    void ParseClassStmt();
    void ParseWhileStmt();
    void ParseSingleStmt();
    void ParseFunctionStmt();
    void ParseFunctionParam();
};

#endif
