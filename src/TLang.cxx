#include <iostream>
#include <fstream>
#include "VM.h"
#include "Parser.h"
#include "IRBuilder.h"
#include "CFunction.h"
using namespace std;

int main(int argc, char* argv[]){
    ifstream src;
    Parser* parser;

    if(argc <= 1) cerr << "Error: Need a file name\n";
    src.open(argv[1], std::ifstream::in);

    IRBuilder* builder = new IRBuilder();
    parser = new Parser(&src);

    NodeAST* root = parser->Parse();
    root->GenerateIR(builder);

    CFunction::Init(builder);
    VM::ExecCode(builder->GetCodeObject());
}                                                      

