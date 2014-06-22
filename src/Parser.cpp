/**
 * What is the parser going to do?
 *
 * 1. Main is going to call parser with an istream.
 * 2. Parser creates an instance of the lexer with the istream
 *
 */
#include <istream>
#include <fstream>
#include <iostream>
#include "Debug.h"
#include "Parser.h"
#include "Lexer.h"
#include "Token.h"
#include "Ast/SeqAst.h"
#include "Ast/IfStmtAst.h"
#include "Ast/CallAst.h"
#include "Ast/ExprAst.h"
#include "Ast/ParamAst.h"
#include "Ast/FunctionStmtAst.h"
#include "Ast/WhileStmtAst.h"
#include "Ast/ClassStmtAst.h"
#include "Ast/ForStmtAst.h"
#include "Ast/ListAst.h"
#include "IrBuilder.h"
#include "OpToken.h"

short getPrecedence(SToken t) {
  if (t->getTag() == Tags::BSQO)
    return 100;
  OpToken *opt = GUARD_CAST<OpToken *>(t.get());
  switch (opt->getValue()) {
  case Opc::AND:
  case Opc::OR:
    return 0;
  case Opc::LT:
  case Opc::LEQ:
  case Opc::GT:
  case Opc::GEQ:
  case Opc::NEQ:
  case Opc::EQ:
    return 10;
  case Opc::BOR:
    return 20;
  case Opc::XOR:
    return 30;
  case Opc::BAND:
    return 40;
  case Opc::LSHIFT:
  case Opc::RSHIFT:
    return 50;
  case Opc::ADD:
  case Opc::SUB:
    return 60;
  case Opc::MULT:
  case Opc::DIV:
  case Opc::MOD:
    return 70;
  case Opc::POWER:
    return 80;
  case Opc::INV:
    return 90;
  default:
    return 100;
  }
}

Parser::Parser(std::istream *i) { lexer_ = std::make_shared<Lexer>(i); }

void Parser::move() { look_ = lexer_->scan(); }

SNodeAst Parser::parse() {
  /*
   * Block => [Stmt]*
   * Stmt => ifStmt, tryStmt, forStmt, whileStmt...
   * ifStmt =>
   */
  move();
  return parseBlock();
}

SNodeAst Parser::parseFunctionParam(bool isCall = false) {
  // 1. Functions can have no parameter
  //   defun bla
  //      [print: Hello]
  //   endfun
  // 2. Functions can have one or more parameter
  //   defun blaWithA:a andB:b
  //      [print: a+b]
  //      [print: a + b andB:
  //   endfun
  //
  // 3. Functions can have other functions as param
  //   defun funcWithCb:(cb:a andB:b) andB:b
  //      //do something
  //   endfun
  SNodeAst param;
  auto p = std::make_shared<ParamAst>();
  auto lw = GUARD_CAST<WordToken *>(look_.get());
  switch (look_->getTag()) {
  case Tags::ID:
  case Tags::STR:
    p->addParam(lw->getValue(), nullptr);
    move();
    break;
  case Tags::PARAM:
    while (look_->getTag() == Tags::PARAM) {
      param = look_;
      lw = GUARD_CAST<WordToken *>(look_.get());
      move();
      // is it a [] grouping, only possible in a func call
      if (isCall && look_->getTag() == Tags::BSQO) {
        p->addParam(lw->getValue(), parseFunctionCall());
      } else if (look_->getTag() == Tags::BCIO) {
        // is it a () grouping
        if (!isCall)
          move(); // consume the (
        // Seems to be a function
        if (look_->getTag() == Tags::PARAM)
          p->addParam(lw->getValue(), parseFunctionParam());
        else {
          p->addParam(lw->getValue(), parseExpr());
        }
        if (!isCall)
          move(); // consume the ))
      } else if (look_->getTag() == Tags::BCIC) {
        move();
        break;
      } else {
        // its a simple id
        if (isCall) {
          p->addParam(lw->getValue(), parseExpr());
        } else {
          p->addParam(lw->getValue(), look_);
          move();
        }
      }
    }
    break;
  default:
    assert(false);
    // throw an error. Function is malformed
  }
  return p;
}

/*
 *            CALL_N
 *       OBJ_N    PARAM_N
 *
 */
SNodeAst Parser::parseFunctionCall() {
  move(); // consume [
  auto call = std::make_shared<CallAst>();
  switch (look_->getTag()) {
  case Tags::PARAM: //[call:2 withb:]
    call->setRight(parseFunctionParam(true));
    break;
  case Tags::BSQO: //[[obj init] doSmth:a]
    call->setLeft(parseFunctionCall());
    call->setRight(parseFunctionParam(true));
    break;
  case Tags::ID: {
    auto tmp = look_;
    move();
    if (look_->getTag() != Tags::BSQC) {
      call->setLeft(tmp);
      call->setRight(parseFunctionParam(true)); //[obj some]
    } else {
      auto param = std::make_shared<ParamAst>();
      std::string fName = GUARD_CAST<WordToken *>(tmp.get())->getValue();
      param->addParam(fName);
      call->setRight(param); // [func]
    }
    break;
  }
  default:
    assert(false);
  }
  move(); // consume the ending ']'
  return call;
}

/*
 *       F_NODE
 *   FPAR_N  F_BLOCK
 *
 */
SNodeAst Parser::parseFunctionStmt() {
  /*
   * defun bla
   *    [print: something]
   * endfun
   *
   * defun funWith:a andB:b
   * defun funWith:(funWithA:B:) andB:b
   * endfun
   */
  // consume defun or defcon
  bool isinit = look_->getTag() == Tags::DEFCON;
  move();

  auto param = parseFunctionParam();
  auto block = parseBlock();
  auto funcDef = std::make_shared<FunctionStmtAst>(isinit, param, block);

  // consume the endfun
  // TODO use matchAndMove instead to make sure that the syntax is valid
  move();
  return funcDef;
}

SNodeAst Parser::parseSingleStmt() {
  /*
   * var a = 2
   * var b = (2 + 2)
   * ac  = 2 //Error ac has not been declared
   * [smth]
   *
   */
  //[smth]
  if (look_->getTag() == Tags::BSQO) {
    return parseFunctionCall();
  }
  SNodeAst node = nullptr;

  if (look_->getTag() == Tags::VAR) {
    move();
    node = std::make_shared<NodeAst>(NodeType::VAR, look_, nullptr);
    assert(look_->getTag() == Tags::ID);
  }

  if (look_->getTag() == Tags::ID) {
    SToken tmp = look_;
    move(); // move over the variable;
    // var a = smth
    if (look_->getTag() == Tags::ASSIGN) {
      move();
      auto n = std::make_shared<NodeAst>(NodeType::ASSIGN, tmp, parseExpr());
      if (node.get() != nullptr) {
        node->setRight(n);
        return node;
      } else {
        return n;
      } // a = smth;
    } else if (node.get() != nullptr) {
      return node;
    } // var a

    // TODO What if the single statement has a single variable only?
    assert(false);
  }

  // make sure that that the var keyword has not been found
  assert(node.get() == nullptr);
  assert(look_->getTag() != Tags::ASSIGN);

  switch (look_->getTag()) {
  case Tags::RETURN:
    move();
    return std::make_shared<NodeAst>(NodeType::RETURN, parseExpr(), nullptr);
    break;
  case Tags::BREAK:
    move();
    return std::make_shared<NodeAst>(NodeType::BREAK, nullptr, nullptr);
    break;
  default:
    assert(false);
  }

  return node;
}

/*
 * {}
 *
 */
SNodeAst Parser::parseList() {
  assert(look_->getTag() == Tags::BCUO);
  auto listast = std::make_shared<ListAst>();
  // bool end = false;
  do {
    // at the start we are consuming the '{', from then on
    // we are consuming a ','
    move();
    SNodeAst key = parseExpr();
    if (key == nullptr) { /*end = true;*/
      break;
    }
    auto isDict = look_->getTag() == Tags::DSEP ? true : false;
    if (isDict) {
      move();
      listast->addPair(key, parseExpr());
    } else {
      listast->addPair(nullptr, key);
    }
  } while (look_->getTag() == Tags::CSEP);
  // TODO, check if the next character is a '}'
  // TODO, in case of a end = true, make sure that the result was not malformed

  move();
  return listast;
}

/*
 * Using the Shunting yard algorithm to turn the infix expr
 * to RPN
 *
 * TODO: Optimization - We can perform open expressions ourselves rather than
 * having the vm do it
 */
SNodeAst Parser::parseExpr() {
  // Expr -> id
  // Expr -> Val
  // Expr -> (Expr op epxr)
  uint currentLine = look_->getLineNo();
  VecSToken opstack;
  VecSToken outstack;
  auto linearExpr = std::vector<SToken>();
  bool stop = false;
  // Stop is needed for cases when the expression does not extend whole line
  // Eg. [someFunc: (a+b) ano:b]
  // Here we dont stop at the end of the line, but when we reach the
  // "ano:" PARAM
  while (!stop && (currentLine == look_->getLineNo())) {
    linearExpr.push_back(look_);
    switch (look_->getTag()) {
    case Tags::BCIO:
      opstack.push_back(look_);
      move(); // consume (
      break;
    case Tags::BCIC:
      while (!opstack.empty()) {
        if (opstack.back()->getTag() == Tags::BCIO) {
          opstack.pop_back();
          break;
        }
        outstack.push_back(opstack.back());
        opstack.pop_back();
      }
      move();
      break;
    case Tags::BSQO: {
      SToken tmp = look_;
      tmp->setLeft(parseFunctionCall());
      outstack.push_back(tmp);
      break;
    }
    case Tags::BCUO: {
      SToken tmp = look_;
      tmp->setLeft(parseList());
      outstack.push_back(tmp);
      break;
    }
    case Tags::ID:
    case Tags::NUM:
    case Tags::REAL:
    case Tags::STR:
      outstack.push_back(look_);
      move();
      break;
    case Tags::OP: {
      /*
       * Handle Unary + and -.
       * If OP is the first token, it is unary. Similarly, if the previous token
       * is a OP, we have a unary operator
       * linearExpr[last] contains the current token
       * [linearExpr[last-1] contains the previous token
       *
       * TODO, we can skip if the op is a UNARY_ADD
       */
      Opc opc = GUARD_CAST<OpToken *>(look_.get())->getValue();
      if (opc == Opc::SUB) {
        SToken sndLast;
        if (linearExpr.size() > 1) {
          sndLast = linearExpr[linearExpr.size() - 2];
        }
        if (sndLast == nullptr || sndLast->getTag() == Tags::OP) {
          opc = Opc::UNARY_SUB;
          look_ = std::make_shared<OpToken>(opc, look_->getLineNo());
        }
      }

      while (!opstack.empty() && (opstack.back()->getTag() != Tags::BCIO)) {
        if (getPrecedence(look_) <= getPrecedence(opstack.back())) {
          outstack.push_back(opstack.back());
          opstack.pop_back();
        } else
          break;
      }
      opstack.push_back(look_);
      move();
      break;
    }
    default:
      stop = true;
      break;
    }
  }
  while (!opstack.empty()) {
    outstack.push_back(opstack.back());
    opstack.pop_back();
  }
  int count = outstack.size();
  if (count == 0)
    return std::shared_ptr<NodeAst>(nullptr);
  return std::make_shared<ExprAst>(outstack);
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
SNodeAst Parser::parseIfStmt() {
  // ifStmt -> if (bool) block [elif block] [else block] endif
  // consume if
  move();
  auto expr = parseExpr();
  auto block = parseBlock();
  auto stmt = std::make_shared<IfStmtAst>(expr, block);
  if (look_->getTag() == Tags::ELIF) {
    assert(false && "Not supported");
  }
  if (look_->getTag() == Tags::ELSE) {
    move();
    stmt->setElseBlk(parseBlock());
  }
  // consume endif
  move();
  return stmt;
}

/*
 * for x in y
 * endfor
 *
 * x is a simple identifier. y is an expression/identifier that represents a
 * iterator
 */
SNodeAst Parser::parseForStmt() {
  // consume the for
  move();
  // consume the identifier
  auto ident = look_;
  move();
  // consume the in
  move();
  // consume the iterator or an expression that generates an iterator
  auto iter = parseExpr();
  // parse the body of the loop
  auto body = parseBlock();
  // consume endfor
  move();
  return std::make_shared<ForStmtAst>(ident, iter, body);
}

SNodeAst Parser::parseTryStmt() { return nullptr; }

SNodeAst Parser::parseClassStmt() {
  // consume 'defclass'
  move();
  // TODO handle 'isa' for class inheritencec;
  auto className = look_;
  move();
  auto classAst = std::make_shared<ClassStmtAst>(className, parseBlock());

  // consume the endclass
  move();
  return classAst;
}

SNodeAst Parser::parseWhileStmt() {
  // consume while
  move();
  auto expr = parseExpr();
  auto block = parseBlock();
  auto stmt = std::make_shared<WhileStmtAst>(expr, block);
  // consume endwhile
  move();
  return stmt;
}

SNodeAst Parser::parseImportStmt() {
  static std::map<std::string,SNodeAst> parsedImports;

  //consume 'import'
  auto line = look_->getLineNo();
  std::vector<std::string> path;
  move();
  while(look_->getLineNo() == line){
    auto lw = GUARD_CAST<WordToken *>(look_.get());
    path.push_back(lw->getValue());
    move();
  }
  //can either be a * or a function/property/class
  std::string importObj = path.back();
  path.pop_back();
  SNodeAst root;
  if(path.size() > 0){
    std::string filePath = "";
    for(auto i : path){
      //TODO, dont hardcode the seperator
      filePath += i + '/';
    }
    //get rid of the last '/'.
    filePath.pop_back();
    if (parsedImports.find(filePath) == parsedImports.end()) {
      std::ifstream src;
      src.open(filePath.c_str(), std::ifstream::in);
      auto parser = std::make_shared<Parser>(&src);
      root = parser->parse();
      parsedImports[filePath] = root;
    }
    else{
      root = parsedImports[filePath];
    }
  }

  return std::make_shared<ImportAst>(importObj, root);
}

/*
 *                             SeqAST
 *                         STMT   SEQ
 *                              STMT  SEQ
 *                                 ...
 */
SNodeAst Parser::parseBlock() {
  // Block -> Stmts...
  SSeqAst s = std::make_shared<SeqAst>();
  SSeqAst ts = s;
  SNodeAst tmp;
  while (true) {
    switch (look_->getTag()) {
    // blocks
    case Tags::DEFCLASS:
      tmp = parseClassStmt();
      break;
    case Tags::DEFCON:
    case Tags::DEFUN:
      tmp = parseFunctionStmt();
      break;
    case Tags::IF:
      tmp = parseIfStmt();
      break;
    case Tags::FOR:
      tmp = parseForStmt();
      break;
    case Tags::TRY:
      tmp = parseTryStmt();
      break;
    case Tags::WHILE:
      tmp = parseWhileStmt();
      break;
    case Tags::IMPORT:
      tmp = parseImportStmt();
      break;
    // block ends
    case Tags::SEOF:
    case Tags::ENDIF:
    case Tags::ENDFOR:
    case Tags::ENDTRY:
    case Tags::ENDWHILE:
    case Tags::ENDCLASS:
    case Tags::ENDFUN:
    case Tags::ENDCON:
    case Tags::ELSE:
      return ts;
    default:
      tmp = parseSingleStmt();
    }
    s = s->addSeq(tmp);
  }
  return ts;
}
