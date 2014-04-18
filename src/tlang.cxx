//#include "parser.h"
#include "lexer.h"
#include <iostream>
#include <fstream>
using std::cin;
using std::ifstream;

/*                                                      
 *                                                                                                                                          
 *    Send a input stream                                                                                                                   
 *                                                                                                                                          
 *             |                                                                                                                            
 *             |                                                                                                                            
 *             |                                                                                                                            
 *             |                                                                                                                            
 *             |                                                                                                                            
 * Tealang --------> Parser --------> Intermediate (AST) -----------> Virtual Machine                                                       
 *                     ^\             /                                                                                                     
 *                     | \           /                                                                                                      
 *                     v  \         /                                                                                                       
 *                   Lexer \       /                                                                                                                                                       
 *                     ^    \     /                                                                                                                                       
 *                     |     \   /                                                    
 *                     |      \ /                                                     
 *                     +---> Symbol                                                   
 *                           Table                                                    
 *                                                                                    
 */
int main(int argc, char* argv[]){
    Lexer* lex;
    lex = new Lexer(&cin);
    do {
        lex->Next();
        Word* tok = (Word*)lex->GetCurrent();
        if(tok != nullptr){
            std::cout << "<" << tok->lexeme << "> \n";
        }
    } while(lex->GetCurrent()->tag != Tags::SEOF);
        /*
        }
        */

    /*
    TParser* parser;
    ifstream src;
    if(argc == 2){
        src.open(argv[1], std::ifstream::in);
        parser = new TParser(&src);
    }                                                  
    else{                                              
        parser = new TParser(&cin);                          
    }                                                  
    parser->Parse();
    */
}                                                      



