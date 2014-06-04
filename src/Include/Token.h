#ifndef T_TOKEN_H
#define T_TOKEN_H
#include "Common.h"
#include "NodeAst.h"

enum class Tags {
  OP = 256,
  NUM,
  DEFCLASS,
  ENDCLASS,
  DEFUN,
  IF,
  ELIF,
  ELSE,
  ENDIF,
  WHILE,
  TRY,
  CATCH,
  ENDTRY,
  WITH,
  ENDWITH,
  AS,
  IN,
  FOR,
  ENDFOR,
  VAR,
  ISA,
  REAL,
  ID,
  BSQO,
  BSQC,
  SEOF,
  CSEP,
  DSEP,
  STR,
  BCIO,
  BCIC,
  BCUC,
  BCUO,
  BLK,
  ENDBLK,
  FLWBLK,
  CMD,
  PARAM,
  ASSIGN,
  RETURN,
  BREAK,
  ENDFUN,
  ENDWHILE,
  DEFCON,
  ENDCON
};

class Token : public NodeAst {
private:
public:
  const Tags tag_;
  const ulong line_;
  Token(Tags tag, ulong line)
      : NodeAst(NodeType::TOKEN), tag_(tag), line_(line) {}
  virtual ~Token() {}
};

#endif
