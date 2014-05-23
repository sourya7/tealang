#include <iostream>
#include <fstream>
#include <ctime>
#include "VM.h"
#include "Parser.h"
#include "IRBuilder.h"
#include "CFunction.h"
using namespace std;

int main(int argc, char *argv[]) {
  ifstream src;
  SParser parser;
  clock_t start_c = clock();
  clock_t parsed_c;
  clock_t execd_c;

  if (argc <= 1)
    cerr << "Error: Need a file name\n";
  src.open(argv[1], std::ifstream::in);

  auto builder = MakeShared<IRBuilder>();
  CFunction::Init(builder);

  parser = MakeShared<Parser>(&src);
  SNodeAST root = parser->Parse();
  root->GenerateIR(builder);
  parsed_c = clock();

  VM::ExecCode(builder->GetCodeObject());
  execd_c = clock();

  cout << "AST Generetion took: " << (parsed_c - start_c) / 1000.0 << " ms\n";
  cout << "Execution Took: " << (execd_c - parsed_c) / 1000.0 << " ms\n";
}
