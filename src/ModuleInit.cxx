#include "Module.h"
#include "Modules/ListModule.h"
#include "Modules/IOModule.h"

void Module::Init(){
  //AddModule("List", MakeShared<ListModule>());
  AddModule("IO", new IOModule());
}
