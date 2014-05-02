#ifndef T_TOKEN_H
#define T_TOKEN_H
#include "Common.h"
#include "NodeAST.h"

/*
enum class Tags { BAND = 256, BOR, BNOT, BXOR, PLUS, MINUS, MULT, POW,
            MOD, NUM, LSHIFT, RSHIFT, LTE, GTE, LT, GT, EQ, NEQ, AND,
            OR, NOT, DIV, ASSIGN, DEFCLASS, ENDCLASS, DEFFUN, ENDFUN, 
            IF, ELIF, ELSE, ENDIF, WHILE, ENDWHILE, TRY, CATCH, 
            ENDTRY, WITH, ENDWITH, AS, IN, FOR, ENDFOR, VAR, ISA,
            REAL, ID, DECR, INCR, BSQO, BSQC, SEOF, STR, BCIO, BCIC,
            BCUC, BCUO, BLK,ENDBLK,FLWBLK, CMD, PARAM };
            */

enum class Tags { OP = 256, NUM, DEFCLASS, ENDCLASS, DEFUN, ENDFUN, 
            IF, ELIF, ELSE, ENDIF, WHILE, ENDWHILE, TRY, CATCH, 
            ENDTRY, WITH, ENDWITH, AS, IN, FOR, ENDFOR, VAR, ISA,
            REAL, ID, BSQO, BSQC, SEOF, STR, BCIO, BCIC, BCUC, 
            BCUO, BLK,ENDBLK,FLWBLK, CMD, PARAM, ASSIGN, RETURN,
            BREAK };

class Token : public NodeAST {
private:
public:
    const Tags tag;
    const ulong line;
    Token(Tags t, ulong l) : NodeAST(NodeType::TOKEN), tag(t), line(l) {}
    virtual ~Token() {}
};

#endif
