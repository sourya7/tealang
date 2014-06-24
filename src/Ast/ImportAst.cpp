#include "Ast/ImportAst.h"
#include "Module.h"
#include "IrBuilder.h"

/*
 * var obj = [Animal init] --> CallMethod('Animal', 'init')
 * [Animal staticFunc]     --> CallMethod('Animal', 'staticFunc')
 * [Animal method]         --> CallMethod('
 * [obj method]            --> CallMethod('obj', 'method')
 * [obj method]        --> CallMethod('obj', 'invalid')
 * [invalid method]    --> CallMethod('invalid', 'invalid')
 *
 */
void ImportAst::generateIr(SIrBuilder b) {
  SIrBuilder builder = IrBuilder::getGlobalIrBuilder();
  if (left_ == nullptr) {
    // we might have a module
    if (Module::isKnownModule(moduleName_)) {
      Module::loadModule(moduleName_, builder);
    } else {
      std::cerr << "Trying to load " << moduleName_ << " failed!\n";
      assert(false);
    }
  } else {
    // TODO, this leads to a bug if the new file has code outside blocks
    // TODO, we should require a main function
    left_->generateIr(builder);
  }
}
