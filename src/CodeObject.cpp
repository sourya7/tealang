#include <algorithm>
#include "CodeObject.h"

int CodeObject::pushConst(const SObject &o) {
  consts_->push_back(o);
  return consts_->size() - 1;
}

void CodeObject::addVar(std::string name) {
  valmap_[name] = Object::NIL;
}

/*
 * Helper function to find the var in the given CodeObject
 */
std::map<std::string, SObject>::iterator CodeObject::findVar(CodeObject *code,
                                                             std::string var) {
  auto itEnd = code->valmap_.end();
  auto root = code;
  while (root != nullptr) {
    auto it = root->valmap_.find(var);
    if (it != root->valmap_.end()) {
      return it;
    }
    root = root->parent_.get();
  }
  return itEnd;
}

// level returns if we can find it in a parent
SObject CodeObject::getValue(std::string var) {
  auto it = findVar(this, var);
  if(it != this->valmap_.end())
    return it->second;
  return nullptr;
}

void CodeObject::storeValue(std::string var, const SObject &val) {
  auto it = findVar(this, var);
  assert(it != this->valmap_.end() && "Value does not exist!");
  it->second = val;
}

int CodeObject::getChildId(const SCodeObject &c) {
  auto it = std::find(children_->begin(), children_->end(), c);
  if (it != children_->end())
    return it - children_->begin();
  else
    return -1;
}

void CodeObject::addChild(const SCodeObject &child) {
  children_->push_back(child);
}
