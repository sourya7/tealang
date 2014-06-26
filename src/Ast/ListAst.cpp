#include "Ast/ListAst.h"
#include "IrBuilder.h"
#include "Modules/ListModule.h"
#include "Modules/DictModule.h"

void ListAst::addPair(SNodeAst l, SNodeAst r) {
  auto node = std::make_shared<NodeAst>(l, r);
  container_.push_back(node);
}

void ListAst::generateIr(SIrBuilder builder) {
  auto list = ListModule::initInternal();
  auto dict = DictModule::initInternal();
  bool isList = true;
  for (auto v : container_) {
    if(v->getLeft() != nullptr){
      isList = false;
      v->getLeft()->generateIr(builder);
      v->getRight()->generateIr(builder);
      builder->loadConst(dict);
      builder->callMethod("append:WithKey:");
    }
    else {
      assert(isList);
      v->getRight()->generateIr(builder);
      builder->loadConst(list);
      builder->callMethod("append:");
    }
  }
  if(isList)
    builder->loadConst(list);
  else
    builder->loadConst(dict);
}
