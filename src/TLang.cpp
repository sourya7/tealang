#include <iostream>
#include <fstream>
#include <ctime>
#include "Vm.h"
#include "Parser.h"
#include "IrBuilder.h"
#include "Module.h"

int main(int argc, char *argv[]) {
  std::ifstream src;
  SParser parser;

  if (argc <= 1)
    cerr << "Error: Need a file name\n";
  src.open(argv[1], std::ifstream::in);

  SIrBuilder globalScope = std::make_shared<IrBuilder>();

  Module::init();
  Module::loadDefaults(globalScope);

  parser = std::make_shared<Parser>(&src);
  SNodeAst root = parser->parse();
  root->generateIr(globalScope);
  Vm::execCode(globalScope->getCodeObject());
  src.close();
}
