#include <iostream>
#include <fstream>
#include "parser.h"
using namespace std;

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
    ifstream src;
    TParser* parser;
    if(argc == 2){
        src.open(argv[1], std::ifstream::in);
        parser = new TParser(&src);
    }                                                  
    else{                                              
        parser = new TParser(&cin);                          
    }                                                  
    parser->Parse();
}                                                      



