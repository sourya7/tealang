#ifndef T_LEXER_H
#define T_LEXER_H

#include <istream>
#include "Token.h"
#include "WordToken.h"

class Lexer {
private:
  char peek_;
  unsigned long line_;
  std::istream *inputStream_;

  SToken parseNumericToken();
  SToken parseIdentifierToken();
  SToken parseSpecialNumber();
  void readChar();
  bool readAndMatch(char ch);
  SToken parseStringLiteral();

public:
  SToken scan();
  Lexer(std::istream *istream);
};

#endif
