#include "Module.h"
#include "Modules/ListModule.h"
#include "Modules/IOModule.h"

void Module::Init(){
  AddModule("List", new ListModule());
  AddModule("IO", new IOModule());
}
