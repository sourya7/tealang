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
    ifstream src;
    if(argc == 2){
        src.open(argv[1], std::ifstream::in);
        lex = new Lexer(src);
    }                                                  
    else{                                              
        lex = new Lexer(cin);                          
    }                                                  
    lex->PrintAll();                                   
}                                                      


