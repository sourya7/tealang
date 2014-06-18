#include "Module.h"
#include "Modules/ListModule.h"
#include "Modules/IoModule.h"

/*
 * TODO, This file will be generated in the future
 */
void Module::init() {
  addModule("List", std::make_shared<ListModule>());
  addModule("IO", std::make_shared<IoModule>());
}
