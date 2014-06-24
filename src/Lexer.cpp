#include <string>
#include <istream>
#include <iostream>
#include <algorithm>
#include <sstream>
#include "Token.h"
#include "WordToken.h"
#include "NumberToken.h"
#include "RealToken.h"
#include "OpToken.h"
#include "OpCode.h"
#include "Lexer.h"

using namespace std;

/* debug stuff */
map<string, Tags> TokenMap{ { "defclass", Tags::DEFCLASS },
                            { "defcon", Tags::DEFCON },
                            { "defun", Tags::DEFUN },
                            { "if", Tags::IF },
                            { "for", Tags::FOR },
                            { "try", Tags::TRY },
                            { "while", Tags::WHILE },
                            { "elif", Tags::ELIF },
                            { "catch", Tags::CATCH },
                            { "else", Tags::ELSE },
                            { "endif", Tags::ENDIF },
                            { "endfor", Tags::ENDFOR },
                            { "endtry", Tags::ENDTRY },
                            { "endwhile", Tags::ENDWHILE },
                            { "endclass", Tags::ENDCLASS },
                            { "endfun", Tags::ENDFUN },
                            { "endcon", Tags::ENDCON },
                            { "in", Tags::IN },
                            { "var", Tags::VAR },
                            { "isa", Tags::ISA },
                            { "return", Tags::RETURN },
                            { "break", Tags::BREAK },
                            { "import", Tags::IMPORT} };

/*
* Some helper functions for converting from numeric string types
* TODO
*/
int decFromHex(string hexStr) {
  cerr << hexStr;
  return 0;
}

// TODO
int decFromOct(string octStr) {
  cerr << octStr;
  return 0;
}

// TODO
int decFromBin(string binStr) {
  cerr << binStr;
  return 0;
}

int decFromDec(string decStr) { return atoi(decStr.c_str()); }

// TODO
double floatFromFloat(string floatStr) {
  cerr << floatStr;
  return 0;
}

SToken Lexer::parseSpecialNumber() {
  bool isHex = peek_ == 'x';
  bool isOctal = isdigit(peek_);
  bool isBinary = peek_ == 'b';
  if (isHex || isBinary)
    readChar();
  if (isHex || isOctal || isBinary) {
    string tmp;
    do {
      tmp += peek_;
      readChar();
    } while ((isHex && isxdigit(peek_)) || (isOctal && isdigit(peek_)) ||
             (isBinary && (peek_ == '0' || peek_ == '1')));
    return std::make_shared<WordToken>(tmp, Tags::ID, line_);

    /* TODO use these instead
    if(isHex) return new NumberTok(decFromHex(tmp), line_);
    else if(isHex) return new NumberTok(decFromOct(tmp), line_);
    else return new NumberTok(decFromBin(tmp), line_);
    */
  }
  return std::make_shared<NumberToken>(0, line_);
}

SToken Lexer::parseNumericToken() {
  if (peek_ == '0') {
    readChar();
    return parseSpecialNumber();
  }

  // handle decimal numbers
  string tmp;
  do {
    tmp += peek_;
    readChar();
  } while (isdigit(peek_));
  if (peek_ != '.')
    return std::make_shared<NumberToken>(decFromDec(tmp), line_);

  // handle real numbers
  do {
    tmp += peek_;
    readChar();
  } while (isdigit(peek_));
  return std::make_shared<RealToken>(com::strTo<double>(tmp), line_);
}

SToken Lexer::parseIdentifierToken() {
  string tmp;
  while (isalpha(peek_) || isdigit(peek_)) {
    tmp += peek_;
    readChar();
  }
  Tags tag;
  auto it = TokenMap.find(tmp);
  if (peek_ == ':') {
    readChar();
    tmp += ':';
    tag = Tags::PARAM;
  } else if (it != TokenMap.end()) {
    tag = it->second;
    return std::make_shared<Token>(tag, line_);
  } else {
    tag = Tags::ID;
  }

  return std::make_shared<WordToken>(tmp, tag, line_);
}

Lexer::Lexer(istream *i) {
  inputStream_ = i;
  peek_ = ' ';
}

void Lexer::readChar() {
  bool res = inputStream_->get(peek_);
  if (!res || inputStream_->eof())
    peek_ = -1;
}

bool Lexer::readAndMatch(char ch) {
  readChar();
  if (peek_ != ch) {
    return false;
  }
  peek_ = ' ';
  return true;
}

#define IFMATCHELSE(ifMatch, ifTok, elseTok)                                   \
  if (readAndMatch(ifMatch)) {                                                 \
    return std::make_shared<OpToken>(ifTok, line_);                            \
  } else {                                                                     \
    return std::make_shared<OpToken>(elseTok, line_);                          \
  }

#define IFMATCH2ELSE(ifMatch, ifTok, elifMatch, elifTok, elseTok)              \
  if (readAndMatch(ifMatch)) {                                                 \
    return std::make_shared<OpToken>(ifTok, line_);                            \
  } else if (peek_ == elifMatch) {                                             \
    return std::make_shared<OpToken>(elifTok, line_);                          \
  } else {                                                                     \
    return std::make_shared<OpToken>(elseTok, line_);                          \
  }

/*
 * TODO - Handle comments
 * TODO - Use a symbol table to store the identifiers, strings, and numbers
 *
 */
SToken Lexer::scan() {
  // Get rid of the white space
  for (;; readChar()) {
    if (peek_ == '\n') {
      line_ += 1;
    } //
    else if (isspace(peek_)) {
      continue;
    } else {
      break;
    }
  }
  switch (peek_) {
  case '&': { IFMATCHELSE('&', Opc::AND, Opc::BAND); }
  case '|': { IFMATCHELSE('|', Opc::OR, Opc::BOR); }
  case '-': { IFMATCHELSE('-', Opc::DECR, Opc::SUB); }
  case '+': { IFMATCHELSE('+', Opc::INCR, Opc::ADD); }
  case '*': { IFMATCHELSE('*', Opc::POWER, Opc::MULT); }
  case '!': { IFMATCHELSE('=', Opc::NEQ, Opc::NOT); }
  case '<': { IFMATCH2ELSE('=', Opc::LEQ, '<', Opc::LSHIFT, Opc::LT); }
  case '>': { IFMATCH2ELSE('=', Opc::GEQ, '>', Opc::RSHIFT, Opc::GT); }
  case '/': {
    readChar();
    if (peek_ == '/') {
      // its a comment
      while (peek_ != '\n') {
        readChar();
      }
      return scan();
    }
    return std::make_shared<OpToken>(Opc::DIV, line_);
  }
  case '%': {
    readChar();
    return std::make_shared<OpToken>(Opc::MOD, line_);
  }
  case '~': {
    readChar();
    return std::make_shared<OpToken>(Opc::INV, line_);
  }
  case '^': {
    readChar();
    return std::make_shared<OpToken>(Opc::XOR, line_);
  }
  case '[': {
    readChar();
    return std::make_shared<Token>(Tags::BSQO, line_);
  }
  case ']': {
    readChar();
    return std::make_shared<Token>(Tags::BSQC, line_);
  }
  case '(': {
    readChar();
    return std::make_shared<Token>(Tags::BCIO, line_);
  }
  case ')': {
    readChar();
    return std::make_shared<Token>(Tags::BCIC, line_);
  }
  case '{': {
    readChar();
    return std::make_shared<Token>(Tags::BCUO, line_);
  }
  case '}': {
    readChar();
    return std::make_shared<Token>(Tags::BCUC, line_);
  }
  case ',': {
    readChar();
    return std::make_shared<Token>(Tags::CSEP, line_);
  }
  case '.':{
    readChar();
    return std::make_shared<OpToken>(Opc::DOT, line_);
  }
  case '"':
  case '\'': { return parseStringLiteral(); }
  case -1: { return std::make_shared<Token>(Tags::SEOF, line_); }
  case '=': {
    if (readAndMatch('='))
      return std::make_shared<OpToken>(Opc::EQ, line_);
    else
      return std::make_shared<WordToken>('=', Tags::ASSIGN, line_);
  }
  default: {
    return isdigit(peek_) ? parseNumericToken() : parseIdentifierToken();
  }
  }
}

/*
 * TODO - Handle Multi line_ strings
 * TODO - Handle Escape Characters
 *
 * As for the escape characters, only the double quote or the multi line_ quote
 * can represent them. Using the single quote, the escape characters are not
 * interpreted as special characters.
 */
SToken Lexer::parseStringLiteral() {
  string tmp;
  char quote = peek_;
  readChar();
  do {
    if (quote == '"' && tmp.back() == '\\') {
      tmp.pop_back();
      switch (peek_) {
      case 'a':
        tmp += 7;
        break;
      case 'b':
        tmp += 8;
        break;
      case 'e':
        tmp += 27;
        break;
      case 'f':
        tmp += 12;
        break;
      case 'n':
        tmp += 10;
        break;
      case 'r':
        tmp += 13;
        break;
      case 't':
        tmp += 9;
        break;
      case 'v':
        tmp += 11;
        break;
      case '\\':
        tmp += '\\';
        break;
      default:
        break;
      }
    } else
      tmp += peek_;
  } while (!readAndMatch(quote));
  return std::make_shared<WordToken>(tmp, Tags::STR, line_);
}
