#ifndef T_TOKEN_H
#define T_TOKEN_H
#include "Common.h"
#include "NodeAST.h"

enum class Tags { OP = 256, NUM,    DEFCLASS, ENDCLASS, DEFUN, 
                  IF,       ELIF,   ELSE,     ENDIF,    WHILE, 
                  TRY,      CATCH,  ENDTRY,   WITH,     ENDWITH, 
                  AS,       IN,     FOR,      ENDFOR,   VAR, 
                  ISA,      REAL,   ID,       BSQO,     BSQC, 
                  SEOF,     STR,    BCIO,     BCIC,     BCUC, 
                  BCUO,     BLK,    ENDBLK,   FLWBLK,   CMD, 
                  PARAM,    ASSIGN, RETURN,   BREAK,   ENDFUN,
                  ENDWHILE};

class Token : public NodeAST {
private:
public:
    const Tags tag;
    const ulong line;
    Token(Tags t, ulong l) : NodeAST(NodeType::TOKEN), tag(t), line(l) {}
    virtual ~Token() {}
};

#endif
