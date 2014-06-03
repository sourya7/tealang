#include "ListAST.h"
#include "IRBuilder.h"
#include "Modules/ListModule.h"

void ListAST::AddPair(SNodeAST l, SNodeAST r) {
  auto node = MakeShared<NodeAST>(l, r);
  _container.push_back(node);
}

void ListAST::GenerateIR(SIRBuilder builder) {
  VecSObj obj;
  auto list = ListModule::Init(obj);
  for(auto v : _container){
    //TODO make dict work
    v->GetRight()->GenerateIR(builder);
    builder->LoadConst(list);
    builder->CallMethod("append:");
  }
}
