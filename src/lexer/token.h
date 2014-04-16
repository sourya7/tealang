#ifndef T_TOKEN_H
#define T_TOKEN_H

enum Tags { BAND = 256, BOR, BNOT, BXOR, PLUS, MINUS, MULT, POW,
            MOD, NUM, LSHIFT, RSHIFT, LTE, GTE, LT, GT, EQ, NEQ, AND,
            OR, NOT, DIV, ASSIGN, DEFCLASS, ENDCLASS, DEFFUN, ENDFUN, 
            IF, ELIF, ELSE, ENDIF, WHILE, ENDWHILE, TRY, CATCH, 
            ENDTRY, WITH, ENDWITH, AS, IN, FOR, ENDFOR, VAR, ISA,
            REAL, ID, DECR, INCR, BSQO, BSQC, SEOF, STR, BCRO, BCRC};

class Token {
public:
    const Tags tag;
    Token(Tags ptag) : tag(ptag) {}
};

#endif
