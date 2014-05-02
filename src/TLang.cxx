#include <iostream>
#include <fstream>
#include "VM.h"
#include "Parser.h"
#include "IRBuilder.h"
using namespace std;

int main(int argc, char* argv[]){
    ifstream src;
    Parser* parser;

    src.open(argv[1], std::ifstream::in);

    IRBuilder* builder = new IRBuilder();
    parser = new Parser(&src);

    NodeAST* root = parser->Parse();
    root->GenerateIR(builder);

    VM::ExecCode(builder->GetCodeObject());
}                                                      



