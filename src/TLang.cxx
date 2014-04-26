#include <iostream>
#include <fstream>
#include "Parser.h"
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
    Parser* parser;
    if(argc == 2){
        src.open(argv[1], std::ifstream::in);
        parser = new Parser(&src);
    }                                                  
    else{                                              
        parser = new Parser(&cin);                          
    }                                                  
    parser->Parse();
    cout << endl;
}                                                      



