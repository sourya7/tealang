#include "Module.h"
#include "Modules/ListModule.h"
#include "Modules/DictModule.h"
#include "Modules/MathModule.h"
#include "Modules/IoModule.h"
#include "Modules/StringModule.h"
#include "Modules/IntegerModule.h"
#include "Modules/SocketModule.h"

/*
 * TODO, This file will be generated in the future
 */
void Module::init() {
  addModule("List", std::make_shared<ListModule>());
  addModule("Dict", std::make_shared<DictModule>());
  addModule("String", std::make_shared<StringModule>());
  addModule("Integer", std::make_shared<IntegerModule>());
  addModule("IO", std::make_shared<IoModule>());
  addModule("Math", std::make_shared<MathModule>());
  addModule("Socket", std::make_shared<SocketModule>());
}
