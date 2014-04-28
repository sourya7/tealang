#ifndef T_EXPR_H
#define T_EXPR_H

#include "NodeAST.h"

class ExprAST : public NodeAST
{
private:
    vector<Token*> expr;
public:
    ExprAST(vector<Token*> e) : NodeAST(NodeType::EXPR), expr(e) {}


    void Display(int level){ 
        cerr << string(level*2, ' ');
        for(auto t: expr){
            WordTok* w = static_cast<WordTok*>(t);
            cerr << w->lexeme << " ";
        }
        cerr << "\n";
    }

    /*
    string GenOpCode() {
        vector<string> stack;
        string reg = "r0";

        string ret;
        for(auto t : expr){
            WordTok* w = static_cast<WordTok*>(t);
            if(t->tag == Tags::OP){
                ret += w->lexeme + " " + reg + " ";
                ret += stack.back() + " "; stack.pop_back();
                ret += stack.back() + " "; stack.pop_back();
                ret += "\n";
                stack.push_back(reg);
            }
            else {
                stack.push_back(w->lexeme);
            }
            //ret += w->lexeme + " ";
        }
        return ret;
    }
    */
};

#endif
