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
#include <string>
#include <map>
#include "GC.h"
#include "NodeAST.h"
#include "Lexer.h"
#include "Token.h"

using namespace std;

class Parser {
private:
  SToken look;
  SLexer lexer;

public:
  Parser(istream *i);
  void move();

  SNodeAST Parse();
  SNodeAST ParseList();
  SNodeAST ParseBlock();
  SNodeAST ParseIfStmt();
  SNodeAST ParseForStmt();
  SNodeAST ParseTryStmt();
  SNodeAST ParseClassStmt();
  SNodeAST ParseWhileStmt();
  SNodeAST ParseSingleStmt();
  SNodeAST ParseFunctionStmt();
  SNodeAST ParseFunctionParam(bool isCall);
  SNodeAST ParseFunctionCall();
  SNodeAST ParseExpr();
};

#endif
