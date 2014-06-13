#include "Ast/ListAst.h"
#include "IrBuilder.h"
#include "Modules/ListModule.h"

void ListAst::addPair(SNodeAst l, SNodeAst r) {
  auto node = std::make_shared<NodeAst>(l, r);
  container_.push_back(node);
}

void ListAst::generateIr(SIrBuilder builder) {
  VecSObject obj;
  auto list = ListModule::init(obj);
  for (auto v : container_) {
    // TODO make dict work
    v->getRight()->generateIr(builder);
    builder->loadConst(list);
    builder->callMethod("append:");
  }
  builder->loadConst(list);
}
