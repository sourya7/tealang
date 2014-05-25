#ifndef T_LEXER_H
#define T_LEXER_H

#include "GC.h"
#include <string>
#include <istream>
#include "Token.h"
#include "WordTok.h"

using std::string;
using std::istream;

class Lexer {
private:
  char peek;
  unsigned long line;
  istream *inputStream;

  void Reserve(WordTok w);
  SToken ParseNumericToken();
  SToken ParseIdentifierToken();
  SToken ParseSpecialNumber();
  void ReadChar();
  bool ReadAndMatch(char ch);
  SToken ParseStringLiteral();

public:
  SToken Scan();
  Lexer(istream *pistream);
};

#endif
