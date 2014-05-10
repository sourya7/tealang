#include <iostream>
#include <fstream>
#include "VM.h"
#include "Parser.h"
#include "IRBuilder.h"
#include "CFunction.h"
using namespace std;

typedef shared_ptr<Parser> SParser;
int main(int argc, char* argv[]){
    ifstream src;
    SParser parser;

    if(argc <= 1) cerr << "Error: Need a file name\n";
    src.open(argv[1], std::ifstream::in);

    auto builder = std::make_shared<IRBuilder>();
    CFunction::Init(builder);

    parser = make_shared<Parser>(&src);
    SNodeAST root = parser->Parse();
    root->GenerateIR(builder);

    VM::ExecCode(builder->GetCodeObject());
}                                                      

