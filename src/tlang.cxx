#include "parser.h"
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
}                                                      


