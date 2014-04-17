/**
 * What is the parser going to do?
 *
 * 1. Main is going to call parser with an istream.
 * 2. Parser creates an instance of the lexer with the istream
 *
 */
#include <istream>
#include <iostream>
#include "lexer.h"
#include "ltoken.h"

using namespace std;

class TParser {
private:
    istream* inputStream;
public:
    TParser(istream* i) {
        inputStream = i;
    }
    
    /*
     * Do I return something?
     * 1. Create a new environment
     * 2. 
     *
     */
    void Parse(){
        Lexer* lex = new Lexer(inputStream);
        Block* mainBlock = new Block(lex);
        mainBlock->Parse();
    }
};

class Node {
protected:
    Node* left;
    Node* right;
    Token* value; 

public:
    Node(Node* l, Node* r, Token* v) : left(l), right(r), value(v) {}
    Node() {} 
    SetLeft(Node* l) {}
    SetRight(Node* r) {}
    SetValue(Token* v) {}
}

class Block : public Node {
    //Block -> stmt[s]
private: 
    Lexer* lexer;
public:
    Block(Lexer* l) : lexer(l) {} 
    void Parse(){
        Token* tok = lexer->Next();
        switch(tok->tag){
            case Tags::
        }
    }
}
