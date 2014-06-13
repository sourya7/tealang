#ifndef T_TOKEN_H
#define T_TOKEN_H
#include "Common.h"
#include "Ast/NodeAst.h"

enum class Tags {
  OP = 256,
  NUM,      /*257*/
  DEFCLASS, /*258*/
  ENDCLASS, /*259*/
  DEFUN,    /*260*/
  IF,       /*261*/
  ELIF,     /*262*/
  ELSE,     /*263*/
  ENDIF,    /*264*/
  WHILE,    /*265*/
  TRY,      /*266*/
  CATCH,    /*267*/
  ENDTRY,   /*268*/
  WITH,     /*269*/
  ENDWITH,  /*270*/
  AS,       /*271*/
  IN,       /*272*/
  FOR,      /*273*/
  ENDFOR,   /*274*/
  VAR,      /*275*/
  ISA,      /*276*/
  REAL,     /*277*/
  ID,       /*278*/
  BSQO,     /*279*/
  BSQC,     /*280*/
  SEOF,     /*281*/
  CSEP,     /*282*/
  DSEP,     /*283*/
  STR,      /*284*/
  BCIO,     /*285*/
  BCIC,     /*286*/
  BCUC,     /*287*/
  BCUO,     /*288*/
  BLK,      /*289*/
  ENDBLK,   /*290*/
  FLWBLK,   /*291*/
  CMD,      /*292*/
  PARAM,    /*293*/
  ASSIGN,   /*294*/
  RETURN,   /*295*/
  BREAK,    /*296*/
  ENDFUN,   /*297*/
  ENDWHILE, /*298*/
  DEFCON,   /*299*/
  ENDCON    /*300*/
};

class Token : public NodeAst {
private:
  const Tags tag_;
  const ulong line_;

public:
  Tags getTag() { return tag_; }
  ulong getLineNo() { return line_; }
  Token(Tags tag, ulong line)
      : NodeAst(NodeType::TOKEN), tag_(tag), line_(line) {}
  virtual ~Token() {}
};

#endif
