#include <algorithm>
#include "CodeObject.h"

int CodeObject::pushConst(const SObject &o) {
  consts_->push_back(o);
  return consts_->size() - 1;
}

int CodeObject::pushId(std::string var) {
  ids_->push_back(var);
  vals_->push_back(Object::NIL);
  assert(ids_->size() == vals_->size());
  return ids_->size() - 1;
}

// level returns if we can find it in a parent
int CodeObject::getId(std::string var, int &level) {
  level = 0;
  CodeObject *root = this;
  while (root != nullptr) {
    auto it = std::find(root->ids_->begin(), root->ids_->end(), var);
    if (it != root->ids_->end()) {
      return it - root->ids_->begin();
    }
    level++;
    root = root->parent_.get();
  }
  // not found in any level
  level = -1;
  return -1;
}

void CodeObject::storeIdValue(const SObject &val, int id, int level) {
  CodeObject *root = this;
  while (level--) {
    assert(root != nullptr);
    root = root->parent_.get();
  }
  assert(static_cast<int>(root->ids_->size()) > id);
  root->vals_->at(id) = val;
}

int CodeObject::getChildId(const SCodeObject &c) {
  auto it = std::find(children_->begin(), children_->end(), c);
  if (it != children_->end())
    return it - children_->begin();
  else
    return -1;
}

SObject CodeObject::getIdValue(int id, int level) {
  CodeObject *root = this;
  while (level--) {
    assert(root != nullptr);
    root = root->parent_.get();
  }
  return root->vals_->at(id);
}

void CodeObject::addChild(const SCodeObject &child) {
  children_->push_back(child);
}
