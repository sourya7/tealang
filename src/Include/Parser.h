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
#include "NodeAst.h"
#include "Lexer.h"
#include "Token.h"

class Parser {
private:
  SToken look_;
  SLexer lexer_;

public:
  Parser(std::istream *i);
  void move();

  SNodeAst parse();
  SNodeAst parseList();
  SNodeAst parseBlock();
  SNodeAst parseIfStmt();
  SNodeAst parseForStmt();
  SNodeAst parseTryStmt();
  SNodeAst parseClassStmt();
  SNodeAst parseWhileStmt();
  SNodeAst parseSingleStmt();
  SNodeAst parseFunctionStmt();
  SNodeAst parseFunctionParam(bool isCall);
  SNodeAst parseFunctionCall();
  SNodeAst parseExpr();
};

#endif
